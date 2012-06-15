from math import sqrt

critics={'Lisa Rose': {'Lady in the Water': 2.5, 'Snakes on a Plane': 3.5,
      'Just My Luck': 3.0, 'Superman Returns': 3.5, 'You, Me and Dupree': 2.5,
      'The Night Listener': 3.0},
     'Gene Seymour': {'Lady in the Water': 3.0, 'Snakes on a Plane': 3.5,
      'Just My Luck': 1.5, 'Superman Returns': 5.0, 'The Night Listener': 3.0,
      'You, Me and Dupree': 3.5},
     'Michael Phillips': {'Lady in the Water': 2.5, 'Snakes on a Plane': 3.0,
      'Superman Returns': 3.5, 'The Night Listener': 4.0},
     'Claudia Puig': {'Snakes on a Plane': 3.5, 'Just My Luck': 3.0,
      'The Night Listener': 4.5, 'Superman Returns': 4.0,
      'You, Me and Dupree': 2.5},
     'Mick LaSalle': {'Lady in the Water': 3.0, 'Snakes on a Plane': 4.0,
      'Just My Luck': 2.0, 'Superman Returns': 3.0, 'The Night Listener': 3.0,
      'You, Me and Dupree': 2.0},
     'Jack Matthews': {'Lady in the Water': 3.0, 'Snakes on a Plane': 4.0,
      'The Night Listener': 3.0, 'Superman Returns': 5.0, 'You, Me and Dupree': 3.5},
     'Toby': {'Snakes on a Plane':4.5,'You, Me and Dupree':1.0,'Superman Returns':4.0}}

# for twitter get the following
twitter = { 'u1' : { 'h1': 1.0, 'h2': 1.0, 'h3': 1.0 },
             'u2' : { 'h2': 1.0, 'h3': 1.0, 'h4': 1.0 },
             'u3' : { 'h1': 1.0, 'h2': 1.0, 'h4': 1.0, 'h5': 1.0 },
             'u4' : { 'h2': 1.0, 'h4': 1.0, 'h5': 1.0 },
             'u5' : { 'h2': 1.0, 'h4': 1.0, 'h5': 1.0 }
           }

def sim_distance(perfs, x1, x2):
  sum_of_squares = 0.0

  for item in perfs[x1]:
    if item in perfs[x2]:
      sum_of_squares += pow(perfs[x1][item] - perfs[x2][item], 2)

  if sum_of_squares == 0: return 0

  return 1 / (1 + sum_of_squares)

def sim_pearson(perfs, x1, x2):
  sum1 = 0
  sum2 = 0
  sum1_sq = 0
  sum2_sq = 0
  pSum = 0
  n = 0

  for item in perfs[x1]:
    if item in perfs[x2]:
      print "found"
      n = n + 1
      pSum += perfs[x1][item] * perfs[x2][item] 
      sum1 += perfs[x1][item]
      sum2 += perfs[x2][item]
      sum1_sq += pow(perfs[x1][item], 2)
      sum2_sq += pow(perfs[x2][item], 2)

  if n == 0: return 0

  print sum1_sq, sum1
  den = sqrt((sum1_sq - pow(sum1, 2)/n)*(sum2_sq - pow(sum2, 2)/n))
  print den
  if den == 0: return 0

  num = pSum - ((sum1 * sum2)/n)
  return num/den
  

def top_matches(perfs, x, n = 5, similarity = sim_pearson):
  scores = [(similarity(perfs, x, y), y) for y in perfs if y != x]
  scores.sort()
  scores.reverse()
  return scores[0:n]

