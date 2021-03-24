/**
 * StateManager.c
 */

#include "../inc/statemanager.h"

/**
 * This file holds all of the functions for initializing the
 * state engine. This includes the title screen, credits screen,
 * and level transitions.
 * 
 * @author Joseph Deming
 * @author Hunter Craig
 * 
 * @version 1.1.6
 */


/**
 * InitState
 * ------------
 * 
 * Initializes the state machine. This will store states related to
 * the title screen, credits screen, and each level separately.
 * 
 * @param statemanager - the statemanager to be initialized
 * 
 * @return 0 - does nothing
 */
int InitState (StateManager *statemanager) {
    statemanager->capacity = 4; //title screen, credits, and levels. This count will be updated as more levels are added.
    statemanager->stack = malloc(statemanager->capacity * sizeof(State*));
    statemanager->top = -1;
    return 0;
}

/**
 * FreeState
 * ------------
 * 
 * Frees all memory associated with the statemanager, as
 * well as any states within it.
 * 
 * @param statemanager - the statemanager to be destroyed
 * 
 * @return 0 - does nothing
 */
int FreeState (StateManager *statemanager) {
    do {
        PopState(statemanager);
    } while (statemanager->top > -1);
    free(statemanager->stack);
    return 0;
}


/**
 * ScaleState
 * ------------
 * 
 * Increases the maximum capacity of the statemachine,
 * and reallocates data to handle the capacity increase.
 * 
 * @param statemanager - the statemanager to be made larger
 * 
 * @return statemanager->capacity - the new capacity of the statemanager
 */
int ScaleState (StateManager *statemanager) {
    statemanager->capacity *= 2;
    statemanager->stack = realloc(statemanager->stack, statemanager->capacity * sizeof(State*));
    return statemanager->capacity;
}


/**
 * GetTopState
 * ------------
 * 
 * Returns the top state of the statemachine
 * 
 * @param statemanager - the statemanager
 * 
 * @return statemanager->stack[statemanager->top] - the top state
 */
State *GetTopState(StateManager *statemanager) {
    return statemanager->stack[statemanager->top];
}


/**
 * PushState
 * ------------
 * 
 * Pushes a new state to the top of the statemanager.
 * 
 * @param statemanager - the statemanager
 * @param state - the state to be added to the stack
 * 
 * @return statemanager->top - the new top of the stack
 */

int PushState (StateManager *statemanager, State *state) {
    if (statemanager->top + 1 == statemanager->capacity) {
        ScaleState(statemanager);
    }
    statemanager->top++;
    statemanager->stack[statemanager->top] = state;
    if (state->init != NULL) {
        state->init();
    }
    return statemanager->top;

}


/**
 * PopState
 * ------------
 * 
 * Pops a state from the top of the statemanager.
 * 
 * @param statemanager - the statemanager
 * 
 * @return statemanager->top - the new top of the stack
 */
int PopState(StateManager *statemanager) {
    if (statemanager->top == -1) {
        return 0;
    }
    State *top = GetTopState(statemanager);
    if (top->destroy != NULL) {
        top->destroy();
    }
    statemanager->stack[statemanager->top] = NULL;
    statemanager->top--;
    return statemanager->top;
}


/**
 * UpdateState
 * ------------
 * 
 * Calls the update function on the top state.
 * 
 * @param statemanager - the statemanager
 * @param deltatime - the current time
 * 
 * @return state->update(deltatime) - the resulting updated state
 */
int UpdateState(StateManager *statemanager, float deltatime) {
    State *state = GetTopState(statemanager);
    if(state->update != NULL) {
        return state->update(deltatime);
    }
    return 1;
}


/**
 * DrawState
 * ------------
 * 
 * Draws the top state of the statemanager
 * 
 * @param statemanager - the statemanager
 * @param deltatime - the current time
 * 
 * @return state->draw(deltatime) - the drawn state
 */
int DrawState(StateManager *statemanager, float deltatime) {
    State *state = GetTopState(statemanager);
    if(state->draw != NULL) {
        return state->draw(deltatime);
    }
    return 1;
}