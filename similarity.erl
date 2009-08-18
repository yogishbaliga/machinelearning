-module (similarity).

-export( [distance/4] ).

-export( [test_distance/0] ).

%% 
%% @doc Find the similarity between 2 items in a given dictionary of
%%      items. Dict is a dictionary of item to vectors.
%%       
distance(Dict, S1, S2, Fun) ->
  Found = dict:is_key(S1, Dict) andalso dict:is_key(S2, Dict),
  case Found of
    false -> 0.0;
    true ->
      D1 = element(2, dict:find(S1, Dict)),
      D2 = element(2, dict:find(S2, Dict)),
      K1 = sets:from_list(dict:fetch_keys(D1)),
      K2 = sets:from_list(dict:fetch_keys(D2)),
      % find common between S1 and S2
      Common = sets:to_list( sets:intersection(K1, K2) ),
      case length(Common) of
        0 -> 0;
        _ ->
          Fun(Common, dict:to_list(D1), dict:to_list(D2))
      end
  end.

%%
%% @doc Find the cosine distance of 2 vectors
cos_distance(Common, K1, K2) ->
  Squares = 
    lists:map( fun(Key) ->
        {value, {_, V1}} = lists:keysearch(Key, 1, K1),
        {value, {_, V2}} = lists:keysearch(Key, 1, K2),
        math:pow(V1-V2, 2)
      end, Common),
  1/(1+lists:sum(Squares)).

 
pear_distance(Common, K1, K2) ->
  N = length(Common),
  D1 = get_values(Common, K1),
  D2 = get_values(Common, K2),
  Sum1 = lists:sum(D1),
  Sum2 = lists:sum(D2),
  Sum1Squares = sum_of_squares(D1),
  Sum2Squares = sum_of_squares(D2),
  SumOfProduct = sum_of_product(get_values(Common, K1, K2)),
  Den = math:sqrt( (Sum1Squares - math:pow(Sum1, 2)/N) *
                   (Sum2Squares - math:pow(Sum2, 2)/N) ),
  case Den of
    0.0 -> 0.0;
    N1 -> 
      Num = SumOfProduct - ((Sum1 * Sum2)/length(Common)),
      Num/N1
  end.

sum_of_product(List) ->
  lists:sum([V1 * V2 || {V1, V2} <- List]).

sum_of_squares(List) ->
  lists:sum( [math:pow(K, 2) || K <- List] ).

get_values(Keys, List) ->
  lists:flatten([[V || {K1, V} <- List, K1 == K] || K <- Keys]).

get_values(Keys, List1, List2) ->
  lists:flatten( [[{V1, V2} || {K1, V1} <- List1, {K2, V2} <- List2, K1 == K, K2 == K] || K <- Keys] ).

test_distance() ->
  K1 = [{"Lady in the water", 2.5}, {"Snake on a plane", 3.5},
        {"Just my luck", 3.0}, {"Superman returns", 3.5},
        {"You, me and drupee", 2.5}, {"The night listener", 3.0}],
  K2 = [{"Lady in the water", 3.0}, {"Smakes on a plane", 3.5},
        {"Just my luck", 1.5}, {"Superman returns", 5.0},
        {"The night listener", 3.0}, {"You, me and drupee", 3.5}],
  D = dict:from_list([{"Lisa Rose", dict:from_list(K1)}, {"Gene Seymour", dict:from_list(K2)}]),
  io:format( "Cosine distance: ~p~n", [distance(D, "Lisa Rose", "Gene Seymour", fun cos_distance/3)] ),
  io:format( "Pear distance: ~p~n", [distance(D, "Lisa Rose", "Gene Seymour", fun pear_distance/3)] ),
  ok.
  
