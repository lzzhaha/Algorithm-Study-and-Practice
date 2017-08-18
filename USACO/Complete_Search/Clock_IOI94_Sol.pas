program ioi94day2prb1ver1(input, output, inp, out);
{ Tom Verhoeff, Eindhoven University of Technology }
{ Solution that tries all candidate move sequences (modulo order) }

{ General Section }

const
  Test = true ;

var 
  inp, out: text ;

procedure Init ;
  begin
  if Test then
    writeln('IOI''94 - Day 2 - Problem 1: The Clocks') ;
  assign(inp, 'input.txt') ;
  reset(inp) ;
  assign(out, 'output.txt') ;
  rewrite(out) ;
  if Test then writeln('Initialized')
  end { Init } ;

procedure Fini ;
  begin
  close(inp) ;
  close(out)
  end { Fini } ;


{ Problem Specific Section }

procedure inc4(var v: integer) ;
  begin v := succ(v) mod 4 end ;

var
  a, b, c, d, e, f, g, h, i: integer; { state of each dial, in quarter turns }
  n: integer; { # moves in solution }
  move: array [1..27] of integer; { move[1..n] is solution sequence }

procedure ReadInput ;
  { read state of clocks into a .. i }
  begin
  readln(inp, a, b, c) ;
  readln(inp, d, e, f) ;
  readln(inp, g, h, i) ;
  if Test then begin
    writeln('The starting configuration is:') ;
    writeln(a:2, b:2, c:2) ;
    writeln(d:2, e:2, f:2) ;
    writeln(g:2, h:2, i:2)
    end { if }
  end { ReadInput } ;

procedure ComputeAnswer ;
  label 99;
  var
    t1, t2, t3, t4, t5, t6, t7, t8, t9: integer; { move i occurs ti times }
  { N.B. We have not used an array t[1..9] because some Pascal compilers }
  { do not allow array elements as control variables in for-loops. }

  procedure Solution ;
    var m: integer;
    begin
    n := 0 ;
    for m := 1 to t1 do begin inc(n) ; move[n] := 1 end ;
    for m := 1 to t2 do begin inc(n) ; move[n] := 2 end ;
    for m := 1 to t3 do begin inc(n) ; move[n] := 3 end ;
    for m := 1 to t4 do begin inc(n) ; move[n] := 4 end ;
    for m := 1 to t5 do begin inc(n) ; move[n] := 5 end ;
    for m := 1 to t6 do begin inc(n) ; move[n] := 6 end ;
    for m := 1 to t7 do begin inc(n) ; move[n] := 7 end ;
    for m := 1 to t8 do begin inc(n) ; move[n] := 8 end ;
    for m := 1 to t9 do begin inc(n) ; move[n] := 9 end ;
    goto 99
    end { Solution } ;

  begin { ComputeAnswer }
  for t1 := 0 to 3 do begin
    for t2 := 0 to 3 do begin
      for t3 := 0 to 3 do begin
        for t4 := 0 to 3 do begin
          for t5 := 0 to 3 do begin
            for t6 := 0 to 3 do begin
              for t7 := 0 to 3 do begin
                for t8 := 0 to 3 do begin
                  for t9 := 0 to 3 do begin
                    if (a=0) and (b=0) and (c=0) and
                       (d=0) and (e=0) and (f=0) and
                       (g=0) and (h=0) and (i=0) then Solution ;
                    inc4(e) ; inc4(f) ; inc4(h) ; inc4(i)
                    end { for t9 } ;
                  inc4(g) ; inc4(h) ; inc4(i)
                  end { for t8 } ;
                inc4(d) ; inc4(e) ; inc4(g) ; inc4(h)
                end { for t7 } ;
              inc4(c) ; inc4(f) ; inc4(i)
              end { for t6 } ;
            inc4(b) ; inc4(d) ; inc4(e) ; inc4(f) ; inc4(h)
            end { for t5 } ;
          inc4(a) ; inc4(d) ; inc4(g)
          end { for t4 } ;
        inc4(b) ; inc4(c) ; inc4(e) ; inc4(f)
        end { for t3 } ;
      inc4(a) ; inc4(b) ; inc4(c)
      end { for t2 } ;
    inc4(a) ; inc4(b) ; inc4(d) ; inc4(e)
    end { for t1 } ;
  if Test then writeln('No solution found') ;
  99:
  end { ComputeAnswer } ;

procedure WriteOutput ;
  var m: integer;
  begin
  if Test then begin
    write('A ', n:1, '-move solution is:') ;
    for m := 1 to n do
      write(move[m]:2) ;
    writeln
    end { if } ;
  for m := 1 to n do
    write(out, move[m]:2) ;
  writeln(out)
  end { WriteOutput } ;

begin
Init ;
ReadInput ;
ComputeAnswer ;
WriteOutput ;
Fini
end.
