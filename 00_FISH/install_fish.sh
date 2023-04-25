#!/bin/sh

# fish を入れる
sudo apt-add-repository ppa:fish-shell/release-3
sudo apt update
sudo apt install fish

# fish/functions を追加する
cp -r fish/functions ~/.config/fish/
cp -r fish/themes ~/.config/fish/

# config.fish に設定を追加する
cat fish/config.fish >> ~/.config/fish/config.fish

# conda のパスを通す
if type conda > /dev/null 2>&1 ; then
    conda init fish
fi

# fish をデフォルト shell にする
# chsh -s $(which fish)
