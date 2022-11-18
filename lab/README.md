Outline:
- 01_registers
- 02_repl
- 03_sequencer
- 04_slow_motion
- 05_i2c_traffic
- 06_pioscope
- 07_pio_sequencer
- 08_adps_protocol
- 09_lab_on_a_chip
- 10_protoboard
- EC_analog_knob
- EC_ansi_escapes
- EC_asm_registers
- EC_dma_i2c
- EC_hardware_i2c
- EC_interrupt_i2c
- EC_lovr_viz
- EC_pwm_scope
- EC_socket_server
- EC_speaker

Which parts of the lab specification have you found most confusing or difficult to understand? Be specific, and quote any parts of the lab description relevant to your answer (e.g., "modify the PIO/DMA logic analyzer example to record a timestamped trace of an RP2040-ADPS9960 exchange while the BOOT button is pressed.") I will make particular notice of anything that seems underspecified (e.g., words whose meaning is not clear from context, or conflicting interpretations of a deliverable).

For the part I completed/in-progress, the specification I found most confusing is are about part 7 and 8:

- For part 7: "modify your sequencer to use the PIO as its primary I/O engine"
- For part 8: "Use the capabilities of your sequencer to implement the ADPS9960 protocol and control the sensor."

Which lab topics have you found most confusing or difficult to understand? E.g., "serial communication with Python," "aliased bitwise operations," "programming the PIO," etc. Be specific, and describe any lingering areas of confusion and/or anything that has helped you navigate them.

Similarly, the topics I found confusing are part 7 and 8:

- For part 3: I did not understand how we need to use PySerial for recording and replay
- For part 7: I don't understand where should we use PIO. Does it mean we need to use PIO to access button pin?
- For part 8: I don't understand why we need to use sequencer. From part 3, 4, and 7, we use sequencer to record button pressing. So should we also use the button in part 8? 

Which parts of the lab have you found most difficult to implement? Again, be specific, citing any parts of the lab materials & your own code that are relevant to your answer.

It should be from part 6 to 8. I don't know how to measure the timestamped transitions.

What steps have you taken to resolve these difficulties? Any other barriers you have faced to completing this assignment? Mention any students, repos, or other resources you have found helpful in completing the lab so far

I figured out how to use PySerial to interact with c code. Yuxuan Li's part 3 helped me a lot.


