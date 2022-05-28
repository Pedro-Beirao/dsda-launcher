#!/bin/zsh

touch ~/.doom-env.sh
echo "#!/bin/zsh\nlaunchctl setenv DOOMWADDIR \$DOOMWADDIR\nlaunchctl setenv DOOMWADPATH \$DOOMWADPATH" > ~/.doom-env.sh
chmod +x ~/.doom-env.sh

touch ~/Library/LaunchAgents/com.doom.env.plist
echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n <key>Label</key>\n <string>com.doom.env</string>\n <key>Program</key>\n <string>/Users/$USER/.doom-env.sh</string>\n <key>RunAtLoad</key>\n <true/>\n</dict>\n</plist>" > ~/Library/LaunchAgents/com.doom.env.plist

launchctl unload -w ~/Library/LaunchAgents/com.doom.env.plist
launchctl load -w ~/Library/LaunchAgents/com.doom.env.plist

zsh ~/.doom-env.sh