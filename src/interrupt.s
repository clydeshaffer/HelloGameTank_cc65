; ---------------------------------------------------------------------------
; interrupt.s
; ---------------------------------------------------------------------------
;
; Interrupt handler.
;
; Checks for a BRK instruction and returns from all valid interrupts.

.import   _stop, _NMIHandler
.export   _irq_int, _nmi_int

.segment  "CODE"

.PC02                             ; Force 65C02 assembly mode

; ---------------------------------------------------------------------------
; Non-maskable interrupt (NMI) service routine

_nmi_int:  
           JSR _NMIHandler
           RTI                    ; Return from all NMI interrupts

; ---------------------------------------------------------------------------
; Maskable interrupt (IRQ) service routine

_irq_int:  
           SEI
.byte      $9C
.byte      $06
.byte      $40
           CLI
           RTI

; ---------------------------------------------------------------------------
; BRK detected, stop

break:     JMP _stop              ; If BRK is detected, something very bad
                                  ;   has happened, so stop running
