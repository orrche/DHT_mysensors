
ARDUINOPATH="/home/kent/Downloads/arduino-1.8.5"
BOARDNAME="arduino:avr:nano:cpu=atmega328"

TARGET="$(CURDIR)/output"

mysensor_test.ino.hex: mysensor_test.ino
	mkdir -p $(TARGET)
	
	$(ARDUINOPATH)/arduino-builder \
		-build-path $(TARGET) \
		-hardware $(ARDUINOPATH)/hardware \
		-tools $(ARDUINOPATH)/hardware/tools/avr/ \
		-tools $(ARDUINOPATH)/tools-builder/ \
		-libraries $(ARDUINOPATH)/libraries \
		-libraries libraries \
		-fqbn $(BOARDNAME) \
		$<
	
	cp $(TARGET)/$<.hex .

.PHONY: clean

clean:
	rm -rf $(TARGET)
	rm mysensor_test.ino.hex
