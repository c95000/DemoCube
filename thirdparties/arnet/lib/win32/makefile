build: build
all rebuild: clean build install


.PHONEY:
build:
	cd ARCL && $(MAKE)
	cd AR && $(MAKE)
	cd ARNET_SDK && $(MAKE)
	cd ../sdkdemo/Test && $(MAKE)

.PHONEY:
clean:
	cd ARCL && $(MAKE) clean	
	cd AR && $(MAKE) clean
	cd ARNET_SDK && $(MAKE) clean
	cd ../sdkdemo/Test && $(MAKE) clean
	
.PHONEY:
install:
	cd ARCL && $(MAKE) install
	cd AR && $(MAKE) install
	cd ARNET_SDK && $(MAKE) install
	cd ../sdkdemo/Test && $(MAKE) install
