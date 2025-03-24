#!/bin/bash

source .config

# compile both programs
cd server
make
cd ..

cd html_changer
make
cd ..

# adding the boot scripts to the custom-scripts folder
cp  t1_boot_script $custom_scripts_dir

# adds the boot script to the `pre-build.sh`
echo "cp \$BASE_DIR/../custom-scripts/t1_boot_script \$BASE_DIR/target/etc/init.d" >> $custom_scripts_dir/pre-build.sh
echo "chmod +x \$BASE_DIR/target/etc/init.d" >> $custom_scripts_dir/pre-build.sh

# adding the program binaries + index.html to the distro
cp server/t1_server $target_root_dir/usr/bin/t1_server
cp html_changer/t1_html_changer $target_root_dir/usr/bin/t1_html_changer

mkdir -p $target_root_dir/var/www/t1
cp index.html $target_root_dir/var/www/t1/index.html

# compiling the distro
cd $target_root_dir/../..
make
