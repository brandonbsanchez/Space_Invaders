class Board {
    constructor() {
        this.height = 600;
        this.width = 800;
        this.link = document.querySelector('#board');
        this.lastTime = 0;
        this.currentTime = 0;
        this.changeTime = 0;
    }
}

class Player {
    constructor() {
        this.x = board.width / 2; //Middle of board
        this.y = board.height - 60; //Almost end of board
        this.width = 20; //Center to one side
        this.leftKeyPressed = false;
        this.rightKeyPressed = false;
        this.spaceBarPressed = false;
        this.maxSpeed = 600;

        //Creates image of ship and puts it in position
        this.player = document.createElement('img');
        this.player.src = 'images/player.png';
        this.player.id = 'player';
        board.link.appendChild(this.player);
        this.setPosition();
    }

    setPosition() {
        this.player.style.transform = `translate(${this.x}px, ${this.y}px)`; //CSS animation to move player
    }

    updatePlayer() { //Changes x value and moves player
        if(this.leftKeyPressed) {
            this.x -= board.changeTime * this.maxSpeed;
        }
        if(this.rightKeyPressed) {
            this.x += board.changeTime * this.maxSpeed;
        }

        this.restrict();
        this.setPosition();
    }

    restrict() { //Prevents player from going off screen
        if(this.x < this.width) {
            this.x = this.width;
        }
        else if(this.x > board.width - this.width) {
            this.x = board.width - this.width;
        }
    }
}

function update() { //Updates board
    board.currentTime = Date.now();
    board.changeTime = (board.currentTime - board.pastTime) / 1000.0; //Prevents player movement depending on PC clock speed
    player.updatePlayer();
    board.pastTime = board.currentTime;

    window.requestAnimationFrame(update);
}
function onKeyDown(event)
{
    if(event.key === 'a') {
        player.leftKeyPressed = true;
    }
    else if(event.key === 'd') {
        player.rightKeyPressed = true;
    }
    else if(event.key === ' ') {
        player.spaceBarPressed = true;
    }
}
function onKeyUp(event)
{
    if(event.key === 'a') {
        player.leftKeyPressed = false;
    }
    else if(event.key === 'd') {
        player.rightKeyPressed = false;
    }
    else if(event.key === ' ') {
        player.spaceBarPressed = false;
    }
}

//'Main' Starts Here

const board = new Board();
const player = new Player();

window.addEventListener('keydown', onKeyDown);
window.addEventListener('keyup', onKeyUp);
window.requestAnimationFrame(update);