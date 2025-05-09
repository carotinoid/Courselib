# 20230840 곽민성(Minseong Gwak)

import util, math, random
from collections import defaultdict
from util import ValueIteration


############################################################
# Problem 1a: BlackjackMDP

class BlackjackMDP(util.MDP):
    def __init__(self, cardValues, multiplicity, threshold, peekCost):
        """
        cardValues: array of card values for each card type
        multiplicity: number of each card type
        threshold: maximum total before going bust
        peekCost: how much it costs to peek at the next card
        """
        super().__init__()

        self.cardValues = cardValues
        self.multiplicity = multiplicity
        self.threshold = threshold
        self.peekCost = peekCost

    # Return the start state.
    # Look at this function to learn about the state representation.
    # The first element of the tuple is the sum of the cards in the player's
    # hand.
    # The second element is the index (not the value) of the next card, if the player peeked in the
    # last action.  If they didn't peek, this will be None.
    # The final element is the current deck.
    def startState(self):
        return (0, None, (self.multiplicity,) * len(self.cardValues))  # total, next card (if any), multiplicity for each card

    # Return set of actions possible from |state|.
    # You do not need to modify this function.
    # All logic for dealing with end states should be done in succAndProbReward
    def actions(self, state):
        return ['Take', 'Peek', 'Quit']

    # Return a list of (newState, prob, reward) tuples corresponding to edges
    # coming out of |state|.  Indicate a terminal state (after quitting or
    # busting) by setting the deck to None. 
    # When the probability is 0 for a particular transition, don't include that 
    # in the list returned by succAndProbReward.
    def succAndProbReward(self, state, action):
        # BEGIN_YOUR_ANSWER (our solution is 44 lines of code, but don't worry if you deviate from this)

        succ = []

        if(state[2] != None):
            if(action == 'Take'):
                if(state[1] != None):
                    deckCardCounts = tuple(state[2][j]+(-1 if j == state[1] else 0) for j in range(len(state[2])))
                    if(sum(deckCardCounts) == 0): deckCardCounts = None
                    if(state[0]+self.cardValues[state[1]] > self.threshold): deckCardCounts = None

                    nextState = (state[0]+self.cardValues[state[1]], None, deckCardCounts)
                    prob = 1
                    reward = (0 if deckCardCounts != None or nextState[0] > self.threshold else nextState[0])

                    succ.append((nextState, prob, reward))
                else:
                    S = sum(state[2])
                    for i, cnt in enumerate(state[2]):
                        if(cnt == 0): continue
                        
                        deckCardCounts = tuple(state[2][j]+(-1 if j == i else 0) for j in range(len(state[2])))
                        if(sum(deckCardCounts) == 0): deckCardCounts = None

                        if(state[0] + self.cardValues[i] > self.threshold): deckCardCounts = None

                        nextState = (state[0]+self.cardValues[i], None, deckCardCounts)
                        prob = cnt/S
                        reward = (0 if deckCardCounts != None or nextState[0] > self.threshold else nextState[0])

                        succ.append((nextState, prob, reward))

            if(action == 'Peek'):
                if(state[1] != None): pass
                else:
                    S = sum(state[2])
                    for i, cnt in enumerate(state[2]):
                        if(cnt == 0): continue

                        nextState = (state[0], i, state[2])
                        prob = cnt/S
                        reward = -self.peekCost

                        succ.append((nextState, prob, reward))
            
            if(action == 'Quit'): succ.append(((state[0], None, None), 1, state[0]))

        return succ
    
        # END_YOUR_ANSWER

    def discount(self):
        return 1

############################################################
# Problem 1b: ValueIterationDP

class ValueIterationDP(ValueIteration):
    '''
    Solve the MDP using value iteration with dynamic programming.
    '''
    def solve(self, mdp):
        V = {}  # state -> value of state

        # BEGIN_YOUR_ANSWER (our solution is 13 lines of code, but don't worry if you deviate from this)

        inf = 1e18

        def dfs(state):
            if(state in V): return V[state]
            if(state[2] == None):
                V[state] = 0
                return V[state]

            v = -inf
            for action in mdp.actions(state):
                action_v = 0
                for (next_state, prob, reward) in mdp.succAndProbReward(state, action):
                    action_v += (reward + dfs(next_state)*mdp.discount()) * prob
                
                v = max(v, action_v) 
            V[state] = v
            return V[state]

        dfs(mdp.startState())

        # END_YOUR_ANSWER

        # Compute the optimal policy now
        pi = self.computeOptimalPolicy(mdp, V)
        self.pi = pi
        self.V = V

############################################################