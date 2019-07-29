.equ PERI_BASE, 0x3f000000				@Peripheral Base Address
.equ GPIO_BASE, PERI_BASE + 0x00200000	@GPIO Base Address

.section ".text.boot"
.global _start

_start:
	@----------------------------------------------------------
	@	ACT LED Blink
	@----------------------------------------------------------

	LDR R0, =GPIO_BASE
	MOV R1, #1
	LSL R1, #21
	STR R1, [R0, #0x0010]

	MOV R1, #1
	LSL R1, #15

	STR R1, [R0, #0x0020]

	b .

	.end
