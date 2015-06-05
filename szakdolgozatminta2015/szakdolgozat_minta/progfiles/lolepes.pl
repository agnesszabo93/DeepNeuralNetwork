% lolepes(N,Lista) - az NxN-es sakkt�bl�n l�p a l�val,
% adott poz�ci�b�l indulva. A Lista a l�p�sek list�ja.
lolepes(N,Lista):-
    N2 is ceiling(N / 2), numlist(1,N2,NLista),
    member(Kx,NLista), member(Ky,[1,2]),
    egeszit(N,[Kx/Ky],Lista).

% egeszit(N,Lis1,Lis2).
% meg�ll, ha N*N mezon m�r voltunk.
egeszit(N,Lis1,Lis2) :-
    N2 is N * N,
    length(Lis1,N2),
    reverse(Lis1,Lis2),!.

% keres�nk k�vetkezo l�p�st
egeszit(N,[Fej|Mar],Valasz) :-
    egylepes(N,Fej,Utan,Mar),
    egeszit(N,[Utan,Fej|Mar],Valasz).

% egylepes(Ex/Ey,Ux/Uy,Tiltott) - Ex/Ey
% mezorol l�p �gy, hogy a Tiltott
% elemeket ker�li.
egylepes(N,Ex/Ey,Ux/Uy,Tiltott) :-
    LL=[1/2, 2/1, 1/(-2),
       (-2)/1,(-1)/2, 2/(-1),
       (-1)/(-2),(-2)/(-1)],
    member(Ix/Iy,LL),
    Ux is Ex + Ix, Ux > 0, Ux =<N,
    Uy is Ey + Iy, Uy > 0, Uy =<N,
    \+ member(Ux/Uy,Tiltott).

korLepes(N,Lista) :-
    lolepes(N,Lista),
    [Fej|_] = Lista,
    last(Lista,Veg),
    egylepes(N,Fej,Veg,[]).

%%%%%%%%%%%% MEGJELENITES %%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
% osszlepes(N) - ki�rja az �sszes
% lehets�ges bej�r�st, visszal�p�ssel
osszlepes(N) :-
    lolepes(N,Lista),
    tikzKiir(Lista),
    fail.

% tikzKorKiir(Lista) - a listaban szereplo teljes
% l�l�p�s-sort kiirja a Latex-hez - felt�telezi,
% hogy a LISTA k�r.
tikzKorKiir([Fej|Mar]) :-
    % meret megallap�t�sa
    length([Fej|Mar],N2),N is ceiling(sqrt(N2)),
    writeln('\%'),
    writePre(N),
    drawkezd(Fej),
    writeDraw(Mar),
    writeln('    \\draw (start) -- (stop);'),
    writePost,!.

% tikzKiir(Lista) - a listaban szereplo teljes l�l�p�s-sort
% kiirja a Latex-hez kompil�l�sra.
tikzKiir([Fej|Mar]) :-
    % meret megallap�t�sa
    length([Fej|Mar],N2),N is ceiling(sqrt(N2)),
    writeln('\%'),
    writePre(N),
    drawkezd(Fej),
    writeDraw(Mar),
    writeln('    \\node[draw,circle] at (start)  {$\\cdot$};'),
    writeln('    \\node[draw,rectangle] at (stop)  {$\\cdot$};'),
    writePost,!.
    
% Preambulum a TIKZ k�phez
writePre(N) :-
    write('\\begin{tikzpicture}[line width=1.5pt,scale='),
    Sc is min(1.5,3.6/N),
    write(Sc),writeln(']'),
    write('  \\draw[step=1cm,gray!25!red!25!,thick] (-0.1,-0.1) grid ('),
    write(N),write('.1,'),write(N),writeln('.1);'),
    writeln('  \\begin{scope}[color=blue!35!green!,minimum size=0.2cm,\%'),
    writeln('      xshift=-0.5cm,yshift=-0.5cm,inner sep=0pt,outer sep=0pt]').

% drawkezd(Fej) - kiirja a kezdopoz�ci�t �s kezdi vonalat.
drawkezd(Kx/Ky) :-
    write('    \\coordinate (start) at ('),
    write(Kx),write(','),write(Ky),writeln(');'),
    write('    \\draw[rounded corners=1pt] (start)').

% writeDraw(Lista) - befejezi a vonalki�r�st.
writeDraw([Kx/Ky]) :-
    write(' -- ('),write(Kx),write(','),write(Ky),writeln(');'),
    write('    \\coordinate (stop) at ('),
    write(Kx),write(','),write(Ky),writeln(');').
writeDraw([Kx/Ky|Marad]) :-
    write(' -- ('),write(Kx),write(','),write(Ky),write(')'),
    writeDraw(Marad).

writePost :-  % v�ge - nincs param�ter
    writeln('  \\end{scope}\n\\end{tikzpicture}').
