Conducting Research to develop firmware to flash program Droplets wirelessly using Infrared communication. The Droplets are an experimental open-source platform for large-scale swarm research based on ATXmega 128U platform.


Background: 
• The current implementation has a swarm of one hundred Droplets. It is a tedious task to reprogram each and every droplet. To minimize the effort, I am developing firmware to self-program the droplets.

• The entire code is divided into User code and OS code (supports the various functionalities on Droplets) 

• A Master droplet broadcasts the User code wirelessly to the residing Slave droplets and they are programmed directly onto the flash using Self programming: an exclusive feature of ATXmega family.


Working at Correll lab has helped me gaining an in-depth vision on firmware/software development

