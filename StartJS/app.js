class Board {
    constructor() {
        this.height = 600;
        this.width = 800;
        this.link = document.querySelector('#board');
        this.lastTime = 0;
        this.currentTime = 0;
        this.changeTime = 0;
        this.laserCooldown = 0.3;
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
        this.maxSpeed = 600; //Change this to make player faster/slower
        this.lasers = []; //Stores lasers from player
        this.cooldown = 0; //Cooldown to shoot lasers

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
        if(this.spaceBarPressed && this.cooldown <= 0) {
            this.lasers.push(new Laser(this.x, this.y));
            this.cooldown = board.laserCooldown;
        }
        if(this.cooldown > 0) {
            this.cooldown -= board.changeTime;
        }

        this.restrict();
        this.setPosition();
    }

    loopLasers() {
        for(let i = 0 ; i < this.lasers.length ; i++) {
            this.lasers[i].updateLaser();

            if(this.lasers[i].y < 0) {
                this.lasers[i].isDead = true;
                this.lasers[i].removeLaser();
            }
        }
        for(let i = 0 ; i < this.lasers.length ; i++) {
            if(this.lasers[i].isDead === true) {
                this.lasers.splice(i, 1);
                i--;
            }
        }
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

class Laser {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.maxSpeed = 300; //Change to make faster/slower
        this.isDead = false; //Is off screen

        //Creates image of laser and puts it in position
        this.laser = document.createElement('img');
        this.laser.src = 'images/playerLaser.png';
        this.laser.className = 'playerLaser';
        board.link.appendChild(this.laser);
        this.setPosition();
    }

    setPosition() {
        this.laser.style.transform = `translate(${this.x}px, ${this.y}px)`; //CSS animation to move laser
    }
    updateLaser() {
        this.y -= board.changeTime * this.maxSpeed;
        this.setPosition();
    }
    removeLaser() {
        board.link.removeChild(this.laser);
    }
}

function update() { //Updates board
    board.currentTime = Date.now();
    board.changeTime = (board.currentTime - board.pastTime) / 1000.0; //Prevents player movement depending on PC clock speed
    player.updatePlayer();
    player.loopLasers();
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