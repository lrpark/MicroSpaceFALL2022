# MicroSpace2.0
MicroSpace2.0 is an open source framework built of off Microspace, developed by the InSECTS team at Johns Hopkins University, Andrew, Julia, Hunter, and Ryan

Microspace 2.0 was developed by the Water Lily Team at Johns Hopkins University: Laura, Antoine, Coleton, Christina 

# Overview


The repository here contains four main components, a ground system, a client system, a depot system, and common libraries used by all. The ground, client and depot systems are developed to be cloud native in a microservice approach. Within the architecture, every software application deployed and running is containerized and managed by K3S Rancher. Each containerized application is known as either a service or an app, where services are necessary to running the digital ecosystem, and apps are user developed containerized software applications. Both apps and services are built, deployed, and managed the same.


# Setup
Development can proceed in a cloud environment, local virtual machine, or on local hardware. This guide will help the user setup the development environment on a local virtual machine.

1. Download and install a virtual machine client such as virtualbox
2. Download a Linux distro to virtualize. Ubuntu 20 was tested and used during this project.
