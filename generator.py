from random import randint
t = randint(10, 1000)
for _ in range(t):
    menu_option = randint(1, 5)
    print(menu_option, end=" ")
    if menu_option == 1 or menu_option == 2:
        element_to_be_queued = randint(0, 100000)
        print(element_to_be_queued, end="")
    print()
print(0)