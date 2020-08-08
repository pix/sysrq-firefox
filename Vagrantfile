# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/trusty64"

  config.vm.synced_folder ".", "/home/vagrant/project", create: true

	config.vm.provider "virtualbox" do |vb|
		vb.memory = 1024
		vb.cpus = 1
		vb.gui = false
	end

  config.vm.provision "shell", inline: <<-SHELL
		apt-get update
		apt-get install -y \
			build-essential \
			linux-headers-`uname -r` \
			automake \
			git \
			libtool \
			pkg-config
	SHELL
end