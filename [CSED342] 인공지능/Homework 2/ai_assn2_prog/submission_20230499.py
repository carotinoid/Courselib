# 20230499 KIM JaeHwan

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
        curr, next_card, deck = state
        if deck is None:
            return []
        res = []
        total = sum(deck)
        if action == "Quit":
            res.append(((curr, None, None), 1, curr))
        elif action == "Peek":
            if next_card is not None:
                return []
            for i in range(len(deck)):
                if deck[i] > 0:
                    res.append(((curr, i, deck), deck[i] / total, -self.peekCost))
        elif action == "Take":
            if next_card is not None:
                if curr + self.cardValues[next_card] > self.threshold:
                    res.append(((curr + self.cardValues[next_card], None, None), 1, 0))
                else:
                    new_deck = tuple(deck[i] - (1 if i == next_card else 0) for i in range(len(deck)))
                    res.append(((curr + self.cardValues[next_card], None, new_deck), 1, 0))
            else:
                if total == 1:
                    final_index = deck.index(1)
                    res.append(((curr + self.cardValues[final_index], None, None), 1, (0 if curr + self.cardValues[final_index] > self.threshold else curr + self.cardValues[final_index])))
                else:
                    for i in range(len(deck)):
                        if deck[i] > 0:
                            if curr + self.cardValues[i] > self.threshold:
                                res.append(((curr + self.cardValues[i], None, None), deck[i] / total, 0))
                            else:
                                new_deck = tuple(deck[j] - (1 if j == i else 0) for j in range(len(deck)))
                                res.append(((curr + self.cardValues[i], None, new_deck), deck[i] / total, 0))

        return res


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

        def dfs(state):
            curr, next_card, deck = state
            if state in V:
                return V[state]
            if deck == None:
                V[state] = 0
                return V[state]
            val = []
            for action in mdp.actions(state):
                t = 0
                for next, prob, reward in mdp.succAndProbReward(state, action):
                    t += prob * (reward + dfs(next) * mdp.discount())
                val.append(t)
            V[state] = max(val)
            return V[state]
        
        dfs(mdp.startState())
        # END_YOUR_ANSWER

        # Compute the optimal policy now
        pi = self.computeOptimalPolicy(mdp, V)
        self.pi = pi
        self.V = V

############################################################