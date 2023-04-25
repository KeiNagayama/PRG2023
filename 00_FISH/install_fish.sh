#!/bin/sh

# fish を入れる
sudo apt-add-repository ppa:fish-shell/release-3
sudo apt update
sudo apt install fish

# fish の設定を反映する
cp -r fish ~/.config

# conda のパスを通す
if type conda > /dev/null 2>&1 ; then
    conda init fish
fi

# fish をデフォルト shell にする
# chsh -s $(which fish)
