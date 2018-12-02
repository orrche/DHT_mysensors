
BOARDNAME="arduino:avr:mysensor:cpu=atmega328"

TARGET="$(CURDIR)/output"

mysensor_dht.ino.hex: mysensor_dht.ino
	test -n "$(ARDUINOPATH)"  # $$ARDUINOPATH
	mkdir -p $(TARGET)
	
	$(ARDUINOPATH)/arduino-builder \
		-build-path $(TARGET) \
		-hardware hardware \
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
	rm mysensor_dht.ino.hex
