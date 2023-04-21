#!/bin/sh

# fish を入れる
sudo apt-add-repository ppa:fish-shell/release-3
sudo apt update
sudo apt instal fish

# fish/functions を追加する
mv fish/functions ~/.config/fish/
mv fish/themes ~/.config/fish/

# config.fish に設定を追加する
cat fish/config.fish >> ~/.config/fish/config.fish

# conda のパスを通す
conda init fish


# fish をデフォルト shell にする
# sudo chsh -s $(which fish)
