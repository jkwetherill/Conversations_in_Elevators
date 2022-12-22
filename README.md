 # Conversations_in_Elevators
 
 This project simulates the traveling of people through a building, from starting floors onto elevators to destination floors. All the while, in each space, be it a floor or an elevator, all the people there are having a conversation.
 
 The user specifies the people traveling through the building in the file People.txt, which is located in the project directory. Each row represents a person. First the name is listed, then the person's starting floor index is listed, and finally the person's destination floor is listed. The floors are indexed from 0 to 9. The name, starting floor, and destination floor are separated by spaces. Names must not contain spaces.
 
 There are 10 floors, indexed 0 through 9, and 3 elevators, indexed 0 through 2. The number of floors or elevators could be changed by hard-coding a different constant value in the Constants.h file.
 
 In each space, the conversation consists of a list of open questions that have been asked. When a person talks, they first try to answer a question that has been asked. If there are no unanswered questions, the person asks one. Sometimes a person answers their own question.
 
 The simulation outputs sentences to the terminal to specify when each person enters a space (a floor or elevator); what each person is saying and to whom; and when each elevator moves to each floor.
 

