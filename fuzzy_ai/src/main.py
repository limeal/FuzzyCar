##
## KOREA UNIVERSITY PROJECT, 2023
## FuzzyCar
## File description:
## main
##

from network.peer import Peer   

def main():
    # Import Peer class from peer.py file
    peer = Peer("0.0.0.0", 5432)
    peer.start()
    
    while True:
        command = input("Enter command: ")
        if command == "connect":
            peer.connect("0.0.0.0", 4242)
        elif command == "send":
            peer.send("Hello World!")
        elif command == "quit":
            break
        else:
            print("Invalid command")
                


if __name__ == '__main__':
    main()