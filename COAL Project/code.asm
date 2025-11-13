INCLUDE IRVINE32.INC

.DATA
menu byte "---- Menu ----", 0dh,0ah,
          "1- Breakfast", 0dh,0ah, 
          "2- Lunch", 0dh,0ah,
          "3- Dinner",0dh, 0ah,
          "Enter your choise: ", 0

Breakfast byte "---- Breakfast Menu ----", 0dh, 0ah,
               "1- Paratha  - Rs.50", 0dh,0ah, 
               "2- Tea      - Rs.30", 0dh,0ah,
               "3- Omelette - Rs.70",0dh, 0ah,
               "Enter your choise: ", 0

Lunch byte "---- Lunch Menu ----", 0dh, 0ah,
           "1- Biryani - Rs.250", 0dh,0ah, 
           "2- Karahi  - Rs.400", 0dh,0ah,
           "3- Roti    - Rs.20",0dh, 0ah,
           "Enter your choise: ", 0

Dinner byte "---- Dinner Menu ----", 0dh, 0ah,
            "1- Chicken Handi    - Rs.450", 0dh,0ah, 
            "2- Naan (per piece) - Rs.30", 0dh,0ah,
            "3- Cold Drink       - Rs.100",0dh, 0ah,
            "Enter your choise: ", 0

msg1 byte "Enter Quantity: ", 0
More byte "Add more(yes-1 / no-0): ", 0
choise byte "Enter your choise: ", 0

totalNoOfOrders byte 0
orderList byte 100 dup(0)
qtyList byte 100 dup(?)

selectedMenu byte ?
price dword ?
subTotal dword 0
subTotalMsg byte 0dh, 0ah,"Subtotal = ", 0

.CODE
   main proc
    call DisplayMenu
    call calcTotal

   exit
   main endp

   DisplayMenu Proc
   mov edx, offset menu
   call writeString
   call readDec
   mov selectedMenu, al 
   call crlf

   cmp al, 1
   je menu1
   cmp al, 2
   je menu2
       mov edx, offset Dinner
       jmp opt

   menu1:
       mov edx, offset Breakfast
       jmp opt

   menu2:
       mov edx, offset Lunch

   opt:
       call writeString
       call TakingOrder
   
   ret
   DisplayMenu endp

   TakingOrder Proc
    mov esi, 0
   do:
      call readDec
      mov orderList[esi], al
      mov edx, offset msg1
      call writeString
      call readDec
      mov qtyList[esi], al
      call crlf
      inc esi
      inc totalNoOfOrders
      mov edx, offset more
      call writeString
      call readDec

      cmp al, 0
      je e
      mov edx, offset choise
      call writeString
      jmp do

   e:
   ret
   TakingOrder endp

   calcTotal Proc
      movzx ecx, totalNoOfOrders
      mov esi, 0
      cmp selectedMenu, 1
      je menu1
      cmp selectedMenu, 2
      je menu2
         calcOfMenu3:
                     cmp orderList[esi], 1
                     je d1
                     cmp orderList[esi], 2
                     je d2
                          movzx eax, qtyList[esi]
                          mov price , 100
                          mul price
                          jmp loopCond3
                     d1:    
                        movzx eax, qtyList[esi]
                        mov price , 450
                        mul price
                        jmp loopCond3

                     d2:    
                        movzx eax, qtyList[esi]
                        mov price , 30
                        mul price
                       
         loopCond3:
                 add subTotal, eax
                 inc esi
                 loop calcOfMenu3
         jmp TotalOf

      menu1:
         calcOfMenu1:
                     cmp orderList[esi], 1
                     je b1
                     cmp orderList[esi], 2
                     je b2
                          movzx eax, qtyList[esi]
                          mov price , 70
                          mul price
                          jmp loopCond1
                     b1:    
                        movzx eax, qtyList[esi]
                        mov price , 50
                        mul price
                        jmp loopCond1

                     b2:    
                        movzx eax, qtyList[esi]
                        mov price , 30
                        mul price
                       
         loopCond1:
                 add subTotal, eax
                 inc esi
                 loop calcOfMenu1

        jmp TotalOf

      menu2:
         calcOfMenu2:
                     cmp orderList[esi], 1
                     je l1
                     cmp orderList[esi], 2
                     je l2
                          movzx eax, qtyList[esi]
                          mov price , 20
                          mul price
                          jmp loopCond2
                     l1:    
                        movzx eax, qtyList[esi]
                        mov price , 250
                        mul price
                        jmp loopCond2

                     l2:    
                        movzx eax, qtyList[esi]
                        mov price , 400
                        mul price
                       
         loopCond2:
                 add subTotal, eax
                 inc esi
                 loop calcOfMenu2

      TotalOf:
      mov edx, offset subTotalMsg
      call writeString
      mov eax, subTotal
      call writeDec
        
   ret
   calcTotal endp

END MAIN
