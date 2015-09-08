#define NMAX 1

mtype = {incoin, cget, bget, recoin};

chan mcch = [0] of {mtype};
chan stch = [0] of {mtype};

active proctype Machine() {
       int nc = NMAX;
       int nb = NMAX;
       int state = 0;
       do
       :: (state == 0) ->
       	  nc = NMAX; nb = NMAX; printf("MSC: refilled\n");
       :: (state == 0) ->
       	  mcch ? incoin; state = 1;
       :: (state == 1) && (nc== 0) && (nb== 0) ->
       	  stch ! recoin; state = 0;
       :: (state == 1) && (nc> 0) ->
       	  stch ! cget; state = 0;
       :: (state == 1) && (nb> 0) ->
       	  stch ! bget; state =0;
       od;
}

active proctype Student() {
       mtype msg;
       int state = 0;

       do
       :: (state == 0) ->
       	  mcch ! incoin; state = 1;
       :: (state == 1) -> stch ? msg;
       	  if
	  :: (msg == recoin) -> printf("MSC: try again\n");
	  :: (msg == cget) -> printf("MSC: get cola\n");
	  :: (msg == bget) -> printf("MSC: get beer\n");
	  fi;
	  state = 0;
       od;
}