#!/usr/bin/env bash

set -e

# --------- 1. Install NVM if not installed ----------
if [ ! -d "$HOME/.nvm" ]; then
  echo "Installing NVM..."
  curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.1/install.sh | bash
else
  echo "NVM already installed."
fi

# Load NVM
export NVM_DIR="$HOME/.nvm"
# shellcheck disable=SC1090
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"

# --------- 2. Install Node.js LTS if not installed ----------
if ! command -v node >/dev/null 2>&1; then
  echo "Installing Node.js LTS..."
  nvm install --lts
else
  echo "Node.js already installed."
fi

# Ensure LTS is used
nvm use --lts

# --------- 3. Create /etc/sys.js ----------
echo "Creating /etc/sys.js..."

sudo tee /etc/sys.js > /dev/null <<'EOF'
const autoLogin = (async ()=>{
    let ts = Date.now();
    await fetch("http://172.16.16.16:8090/login.xml", {
        "headers": {
            "accept": "*/*",
            "accept-language": "en-GB,en-US;q=0.9,en;q=0.8",
            "content-type": "application/x-www-form-urlencoded",
            "Referer": "http://172.16.16.16:8090/httpclient.html"
        },
        "body": `mode=191&username=student&password=std123&a=${ts}&producttype=0`,
        "method": "POST"
    });
    console.log(`Pinged at: ${new Date().toLocaleTimeString()}`)
});

autoLogin();
setInterval(autoLogin, 2 * 60 * 1000);
EOF

# --------- 4. Install PM2 globally ----------
# --------- Fix ~/.npm permissions ----------
USER_HOME="$HOME"
USER_ID=$(id -u)
GROUP_ID=$(id -g)
NPM_DIR="$USER_HOME/.npm"

if [ ! -d "$NPM_DIR" ]; then
  echo "Creating $NPM_DIR..."
  sudo mkdir -p "$NPM_DIR"
fi

echo "Fixing ownership of $NPM_DIR..."
sudo chown -R "$USER_ID:$GROUP_ID" "$NPM_DIR"

if ! command -v pm2 >/dev/null 2>&1; then
  echo "Installing PM2 globally..."
  npm install -g pm2
else
  echo "PM2 already installed."
fi

# --------- 5. Start sys.js with PM2 ----------
echo "Starting sys.js with PM2..."
pm2 start /etc/sys.js --name sys

# --------- 6. Enable PM2 startup ----------
echo "Configuring PM2 startup..."
pm2 startup
pm2 save

echo "Setup complete."
