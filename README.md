# MicroSpace2.0
MicroSpace2.0 is an open source framework built of off Microspace, developed by the InSECTS team at Johns Hopkins University, Andrew, Julia, Hunter, and Ryan

Microspace 2.0 was developed by the Water Lily Team at Johns Hopkins University: Laura, Antoine, Coleton, Christina 

# Overview

The repository here contains four main components, a ground system, a client system, a depot system, and common libraries used by all. The ground, client and depot systems are developed to be cloud native in a microservice approach. Within the architecture, every software application deployed and running is containerized and managed by K3S Rancher. Each containerized application is known as either a service or an app, where services are necessary to running the digital ecosystem, and apps are user developed containerized software applications. Both apps and services are built, deployed, and managed the same.


# Setup Instructions

Development will happen mainly in a virtual machine. Install VirtualBox or your preferred virtualization product.
Instructions for installing VirtualBox on Windows 10:

[Installation](https://www.youtube.com/watch?v=8mns5yqMfZk)

Using the Raspberry Pi Desktop OS makes for easy deployment to hardware.

[Rasberry Pi OS](https://roboticsbackend.com/install-raspbian-desktop-on-a-virtual-machine-virtualbox/)



## Installation

Inside the Raspberry Pi OS

Install git:
```bash
sudo apt install git-all
```

Install Visual Studio Code or other editor
```bash
sudo apt install code
```

Set up bidirectional clipboard:
[Bidirectional clipboard](https://www.techrepublic.com/article/how-to-enable-copy-and-paste-in-virtualbox/)


Install pyyaml:
```bash
sudo pip install pyyaml
```

Install protobuf compiler:
```bash
sudo apt install protobuf-compiler
```

Install docker:
[Docker](https://www.linuxtechi.com/install-docker-engine-on-debian/)


## Usage

To test basic functionality, inside the main_service directory of one of the spacecraft:
```bash
python3 main_service.py
```
and inside the logger_service directory of the same spacecraft:
```bash
python3 logger_service.py
```
and you should see the output:


## Contributing
Pull requests are welcome. One approval sufficient to merge into develop.