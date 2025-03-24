#!/bin/bash

source .config

cd server
make
cd ..

cd html_changer
make
cd ..

cp server/t1_server $target_root_dir/usr/bin/t1_server
cp html_changer/t1_html_changer $target_root_dir/usr/bin/t1_html_changer

mkdir -p $target_root_dir/var/www/t1
cp index.html $target_root_dir/var/www/t1/index.html

cd $target_root_dir/../..
make
