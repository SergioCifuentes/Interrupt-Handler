cmd_/home/sergio/Interrupt-Handler/module/modules.order := {   echo /home/sergio/Interrupt-Handler/module/driver.ko; :; } | awk '!x[$$0]++' - > /home/sergio/Interrupt-Handler/module/modules.order
