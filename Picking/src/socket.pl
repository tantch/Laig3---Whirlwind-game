%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 Sockets                   %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-use_module(library(sockets)).

port(60070).

% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
        write('teste'),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
        read(Stream,ClientMsg),
        parse_input(ClientMsg,Ans),
        board(Ans,B),
        format(Stream, '~q.~n',[B]),
        flush_output(Stream),
	serverLoop(Stream,B),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream,B) :-
        read(Stream,ClientMsg),
        write('Received: '),write(ClientMsg),nl,
        parse_input(ClientMsg,Answer),
	format(Stream, '~q.~n',[Answer]),
	flush_output(Stream),
        (serverLoop(Stream,B);
	ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input(board(Arg1),Arg1).
parse_input(comando(Arg1, Arg2), Answer) :-
	comando(Arg1, Arg2, Answer).
	
parse_input(quit, ok-bye) :- !.
		
comando(Arg1, Arg2, Answer) :-
	write(Arg1), nl, write(Arg2), nl,
	Answer = 5.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%55

:-use_module(library(random)).
listFullOf(N, [X|Tail],X) :- N > 0, N2 is N-1, listFullOf(N2, Tail,X).
listFullOf(0, [],_).

changeColor(C,Cf):-
        C =:= 1,!,
        Cf is 2;
        C =:= 2,!,
        Cf is 1.

nextLinePrep(F,Fi,C,Cf):-
        F =:= 0,!,
        Cf is C,
        Fi is 3;
        F =:= 1,!,
        Cf is C,
        Fi is 4;
        F =:= 2,!,
        changeColor(C,Cf),
        Fi is 0;
        F =:= 3,!,
        changeColor(C,Cf),
        Fi is 1;
        F =:= 4,!,
        changeColor(C,Cf),
        Fi is 2.
        fillColumn(B,B,T,T,_,_,_).
        fillColumn(B,Bf,T,Col,F-Ci,Cp,FC):-
        Cp<T,
        placePc(Col-Cp,FC,B,B1),
        Cp1 is Cp+5,
        changeColor(FC,Cf),
        fillColumn(B1,Bf,T,Col,F-Ci,Cp1,Cf).

fillColumn(B,Bf,T,Col,F-Ci,_,_):-
        Col1 is Col +1,
        nextLinePrep(F,Fi,Ci,C1),
        fillColumn(B,Bf,T,Col1,Fi-C1,Fi,C1).
       
board(T,Br):-
        listFullOf(T,Rows,0),
        listFullOf(T,B,Rows),
        F is round(T/2 +1 -10),
        F > -1,!,
        fillColumn(B,Br,T,0,F-1,F,1);
        listFullOf(T,Rows,0),
        listFullOf(T,B,Rows),
        F is round(T/2 +1 -5),
        F > -1,
        fillColumn(B,Br,T,0,F-2,F,2).
        membro(X, [X|_]):- !.
        membro(X, [_|Y]):- membro(X,Y).
        concatena([], L, L).

concatena([X|Y], L, [X|Lista]):- concatena(Y, L, Lista).
nth0(0, [Head|_], Head) .
nth0(N, [_|Tail], Elem) :-
        nonvar(N),
        M is N-1,
        nth0(M, Tail, Elem).

nth0(N,[_|T],Item) :-
        var(N),
        nth0(M,T,Item),
        N is M + 1.
        replace(Val,[H|List],Pos,[H|Res]):- Pos > 0, !,
        Pos1 is Pos - 1, replace(Val,List,Pos1,Res).

replace(Val, [_|List], 0, [Val|List]).

placePc(X-Y,C,B,Br):-
        nth0(Y,B,Row),
        replace(C,Row,X,R2),
        replace(R2,B,Y,Br).

element(X1-Y1,C,B):-
        nth0(Y1,B,Row),
        nth0(X1,Row,C).

isEmpty(X-Y,B):-
        element(X-Y,0,B).
isBlack(X1-Y1,B):-
        element(X1-Y1,2,B).
isWhite(X1-Y1,B):-
        element(X1-Y1,1,B).
isColor(X1-Y1,C,B):-
        C == 1,
isWhite(X1-Y1,B).
isColor(X1-Y1,C,B):-
        C == 2,
isBlack(X1-Y1,B).
ligado(X1-Y1,X2-Y2,C,B):-
        isColor(X1-Y1,C,B),
        isColor(X2-Y2,C,B),
        X1 == X2,
        R is Y2 +1,
        Y1 == R.
ligado(X1-Y1,X2-Y2,C,B):-
isColor(X1-Y1,C,B),
isColor(X2-Y2,C,B),
X1 == X2,
R is Y2-1,
Y1 == R.
ligado(X1-Y1,X2-Y2,C,B):-
isColor(X1-Y1,C,B),
isColor(X2-Y2,C,B),
R is X2-1,
Y1 == Y2,
X1 == R.
ligado(X1-Y1,X2-Y2,C,B):-
isColor(X1-Y1,C,B),
isColor(X2-Y2,C,B),
R is X2 +1,
Y1 == Y2,
X1 == R.
inverte([X], [X]).
inverte([X|Y], Lista):- inverte(Y, Lista1), concatena(Lista1, [X], Lista).
winWhite(B):-
length(B,T),
T1 is T-1,
profundidade([], 0-_Yi, T1-_Yf, _Sol_inv,1,B).
winBlack(B):-
length(B,T),
T1 is T-1,
profundidade([], _-0, _-T1, _Sol_inv,2,B).
profundidade(Caminho, Xf-Yf, Xf-Yf, [Xf-Yf|Caminho],_C,_B).
profundidade(Caminho, Xi-Yi, Xf-Yf, Sol,C,B):-
ligado(Xi-Yi, X2-Y2,C,B),
\+ membro(X2-Y2, Caminho),
profundidade([Xi-Yi|Caminho], X2-Y2, Xf-Yf, Sol,C,B).
nextCo(X-Y,Xf-Yf,B):-
length(B,T),
T1 is T-1,
X<T1,!,
Xf is X+1,
Yf is Y;
length(B,T),
T1 is T-1,
Y<T1,!,
Xf is 0,
Yf is Y+1;
Xf is 20,
Yf is 20.
camposVazios(F,20-20,F,_,_):-!.
camposVazios(Lv,X-Y,F,B,C):-
validateMove(X-Y,B,C),
isEmpty(X-Y,B),
nextCo(X-Y,Xf-Yf,B),
camposVazios([X-Y|Lv],Xf-Yf,F,B,C).
camposVazios(Lv,X-Y,F,B,C):-
nextCo(X-Y,Xf-Yf,B),
camposVazios(Lv,Xf-Yf,F,B,C).
isDiag(B,C,Xr-Yr):-
isColor(Xr-Yr,C,B).
areConnected(_X1-Y1,X2-_Y2,B,C):-
Xr is X2,
Yr is Y1,
isColor(Xr-Yr,C,B).
areConnected(X1-_Y1,_X2-Y2,B,C):-
Xr is X1,
Yr is Y2,
isColor(Xr-Yr,C,B).
validDiag(X-Y,B,C,Xr-Yr):-
isDiag(B,C,Xr-Yr),
areConnected(X-Y,Xr-Yr,B,C).
validDiag(_,B,C,Xr-Yr):-
\+ isDiag(B,C,Xr-Yr).
validateMove(X-Y,B,C):-
X1 is X-1,
Y1 is Y-1,
validDiag(X-Y,B,C,X1-Y1),
X2 is X+1,
Y2 is Y-1,
validDiag(X-Y,B,C,X2-Y2),
X3 is X+1,
Y3 is Y+1,
validDiag(X-Y,B,C,X3-Y3),
X4 is X-1,
Y4 is Y+1,
validDiag(X-Y,B,C,X4-Y4).
readComputerRandomType(X):-
random(1,3,X).
readComputerRandomInput(X-Y,B,P):-
camposVazios([],0-0,F,B,P),
length(F,T),
random(0,T,C),
nth0(C,F,X-Y),!,
write(X-Y),nl.
chooseAi(X-Y,F,B,P,R):-
R < 0,!,
X is -1,
Y is -1;
P is 1,
isColor(0-Yr,P,B),
isEmpty(X-Y,B),
membro(X-Y,F),
placePc(X-Y,P,B,Br),
profundidade([], 0-Yr, X-Y, _Sol,P,Br),
X>R;
P =:= 2,
isColor(Xr-0,P,B),
isEmpty(X-Y,B),
membro(X-Y,F),
placePc(X-Y,P,B,Br),
profundidade([], Xr-0, X-Y, _Sol,P,Br),
Y>R;
R1 is R-1,
chooseAi(X-Y,F,B,P,R1).
readComputerAiInput(X-Y,B,P):-
camposVazios([],0-0,F,B,P),!,
length(B,T),
chooseAi(X-Y,F,B,P,T),!,
write(X-Y),nl.
treatInput(B,X-Y,P-M):-
length(B,T),
integer(X),
integer(Y),
X<T,
Y<T,
isEmpty(X-Y,B),
placePc(X-Y,P,B,Br),
validateMove(X-Y,Br,P),!,
changeColor(P,P1),
cycle(Br,P1-M,1).
treatInput(B,_,P-M):-
P=:=1,
M =\=3,
write('Invalid input'),nl,!,
cycle(B,P-M,1);
P=:=2,
M =:= 1,
write('Invalid input'),nl,!,
cycle(B,P-M,1);
cycle(B,P-M,2).
treatInput(B,X1-Y1,X2-Y2,P-M):-
length(B,T),
integer(X1),
integer(Y1),
integer(X2),
integer(Y2),
X1<T,Y1<T,X2<T,Y2<T,
isEmpty(X1-Y1,B),
placePc(X1-Y1,P,B,Br),
isEmpty(X2-Y2,Br),
placePc(X2-Y2,P,Br,Bf),
validateMove(X1-Y1,Bf,P),
validateMove(X2-Y2,Bf,P),
changeColor(P,P1),
cycle(Bf,P1-M,1).
treatInput(B,_,_,P-M):-
P=:=1,
M =\=3,!,
write('Invalid input'),nl,
cycle(B,P-M,1);
P=:=2,
M =:= 1,!,
write('Invalid input'),nl,
cycle(B,P-M,1);
cycle(B,P-M,2).
treatInputType(B,X,P-M):-
integer(X),
X>0,
X<3,
askInput(B,X,P-M).
treatInputType(B,_,P-M):-
P =:= 1,
M =\= 3,!,
write('Invalid input'),nl,
cycle(B,P-M,1);
P=:=2,
M =:= 1,!,
write('Invalid input'),nl,
cycle(B,P-M,1);
cycle(B,P-M,2).
askInput(B,1,P-M):-
P =:= 1,
M =\= 3,
M =\= 5,!,
write('Where do you want to play?(ex: 3-5.)'),nl,
read(X-Y),nl,
treatInput(B,X-Y,P-M);
P =:= 2,
M =:= 1,!,
write('Where do you want to play?(ex: 3-5.)'),nl,
read(X-Y),nl,
treatInput(B,X-Y,P-M);
M<4,!,
readComputerRandomInput(X-Y,B,P),
treatInput(B,X-Y,P-M);
readComputerAiInput(X-Y,B,P),
treatInput(B,X-Y,P-M).
askInput(B,2,P-M):-
P =:= 1,
M =\= 3,
M =\= 5,!,
write('Where do you want to play?(ex: 3-5. 4-5. separete inputs with enter)'),nl,
read(X1-Y1),nl,
placePc(X1-Y1,P,B,Bd),printBoard(Bd),
read(X2-Y2),nl,
treatInput(B,X1-Y1,X2-Y2,P-M);
P=:=2,
M =:= 1,!,
write('Where do you want to play?(ex: 3-5. 4-5. separete inputs with enter)'),nl,
read(X1-Y1),nl,
placePc(X1-Y1,P,B,Bd),printBoard(Bd),
read(X2-Y2),nl,
treatInput(B,X1-Y1,X2-Y2,P-M);
M<4,!,
readComputerRandomInput(X1-Y1,B,P),
placePc(X1-Y1,P,B,Bs),
readComputerRandomInput(X2-Y2,Bs,P),
treatInput(B,X1-Y1,X2-Y2,P-M);
readComputerAiInput(X1-Y1,B,P),
placePc(X1-Y1,P,B,Bs),
readComputerAiInput(X2-Y2,Bs,P),
treatInput(B,X1-Y1,X2-Y2,P-M).
askInputType(B,P-M):-
P =:= 1,
M =\= 3,
M =\= 5,!,
write('Player '),write(P),write(','),nl,
write('How many moves do you want to make? (1/2)'),nl,
read(X),
treatInputType(B,X,P-M);
P =:= 2,
M =:= 1,!,
write('Player '),write(P),write(','),nl,
write('How many moves do you want to make? (1/2)'),nl,
read(X),
treatInputType(B,X,P-M);
M<4,!,
readComputerRandomType(X),
treatInputType(B,X,P-M);
readComputerRandomType(X),!,
treatInputType(B,X,P-M).
startMenu(M,T):-
printMenu,
read(M),nl,
integer(M),
M>0,
M<4,
write('Choose the side of the board: (Pair between 12-20)\n'),
read(T),
integer(T),
T>11,
T<21,
T1 is round(T mod 2),
T1 is 0;
write('invalid input\n'),
startMenu(M,T).
changeM(X,M,Mf):-
X=:=1,!,
Mf is M;
Mf is M+2.
aiMenu(M,Mr):-
M =:= 1,!;
write('What dificulty do you want the computer?(1-Random , 2-AI)'),nl,
read(X),
changeM(X,M,Mr).
start:-
startMenu(M,T),
write(M),nl,
board(T,B),!,
aiMenu(M,Mf),!,
write(Mf),nl,
cycle(B,2-Mf,1).
%P-n jogador M- modo de jogador 1/2/3(humano/random/ai)
cycle(B,_,_):-
winWhite(B),!,
printBoard(B),
write('Player 1 (White) wins the game\n Congrats!\n');
winBlack(B),!,
printBoard(B),
write('Player 2 (Black) wins the game\n Congrats!\n').
cycle(B,P-M,H):-
H=:= 1,
printBoard(B),
askInputType(B,P-M);
askInputType(B,P-M).
