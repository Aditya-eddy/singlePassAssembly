START:  MOV R1,5
        LOAD R2,VAR
        ADD R1,R2
        STORE R1,RESULT
        JMP END

VAR:    10
RESULT: 0

END:    HALT
