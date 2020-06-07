class Board {
    constructor() {
        this.height = 600;
        this.width = 800;
        this.link = document.querySelector('#board');
        this.pastTime = Date.now();
        this.currentTime = 0;
        this.changeTime = 0;
        this.laserCooldown = 0.3;
        this.enemyLaserCooldown = 2.0;
        this.enemiesPerRow = 10;
        this.columns = 3;
        this.enemyHorPadding = 80;
        this.enemyVertPadding = 70;
        this.enemyVertSpacing = 80;
        this.enemyHorSpacing = (this.width - this.enemyHorPadding * 2) / (this.enemiesPerRow - 1);
        this.enemies = [];
        this.enemyLasers = [];
        this.enemyLaserHeight = 20;
        this.isLost = false;
        this.isWon = false;
        this.lostLife = false;
        this.lives = 3;
    }

    updateLives() {
        document.querySelector('#livesLeft').innerHTML = this.lives;
    }
    createEnemies() {
        for(let i = 0 ; i < this.columns ; i++) {
            const y = this.enemyVertPadding + i * this.enemyVertSpacing;

            for(let j = 0 ; j < this.enemiesPerRow ; j++) {
                const x = j * this.enemyHorSpacing + this.enemyHorPadding;
                this.enemies.push(new Enemy(x, y));
            }
        }
    }
    updateEnemies() { //Moves enemies/creates enemy lasers
        const changeX = Math.sin(this.currentTime / 1000.0) * 50;
        const changeY = Math.cos(this.currentTime / 1000.0) * 20;
        
        for(let i = 0 ; i < this.enemies.length ; i++) {
            this.enemies[i].setPosition(changeX, changeY);
            this.enemies[i].cooldown -= this.changeTime;

            if(this.enemies[i].cooldown <= 0) {
                this.enemyLasers.push(new EnemyLaser(this.enemies[i].x + changeX, this.enemies[i].y + changeY));
                this.enemies[i].cooldown = rand(2, 4); //Change these values to change enemy fire rate
            }
        }
    }
    updateEnemyLasers() { //Moves enemy lasers, removes them if they are off board, checks if player gets hit
        for(let i = 0 ; i < this.enemyLasers.length ; i++) {
            this.enemyLasers[i].updateLaser();
            this.enemyLasers[i].checkLaser();
        }
        for(let i = 0 ; i < this.enemyLasers.length ; i++) {
            if(this.enemyLasers[i].isDead === true) {
                this.enemyLasers.splice(i, 1);
                i--;
            }
        }

        const rect1 = player.player.getBoundingClientRect();
        for(let i = 0 ; i < this.enemyLasers.length ; i++) {
            const rect2 = this.enemyLasers[i].laser.getBoundingClientRect();

            if(rectIntersect(rect1, rect2)) { //Player hit
                // board.link.removeChild(player.player);
                // board.link.removeChild(this.enemyLasers[i].laser);

                this.enemyLasers[i].isDead = true;
                this.enemyLasers[i].removeLaser();
                this.lives--;
                this.lostLife = true;
                console.log(this.lives);
                if(this.lives === 0) {
                    return true;
                }
                for(let i = 0 ; i < this.enemyLasers.length ; i++) {
                    if(this.enemyLasers[i].isDead === true) {
                        this.enemyLasers.splice(i, 1);
                        i--;
                    }
                }

                for(let i = 0 ; i < this.enemyLasers.length ; i++)
                {
                    this.enemyLasers[i].removeLaser();
                }
                this.enemyLasers = [];
            }
        }

        return false;
    }
    getShipColor(){
        var temp = document.getElementById("icon");
        var shipColor = temp.src;
        return shipColor;
    }
}

class Player {
    constructor(color) {
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
        this.player.src = color;
        this.player.id = 'player';
        board.link.appendChild(this.player);
        this.setPosition();
    }

    reset() {
        for(let i = 0 ; i < this.lasers.length ; i++) {
            this.lasers[i].removeLaser();
        }
        this.lasers = [];
        this.x = board.width / 2; //Middle of board
        this.y = board.height - 60; //Almost end of board
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
        if(this.spaceBarPressed && this.cooldown <= 0) {
            this.lasers.push(new Laser(this.x, this.y));
            this.cooldown = board.laserCooldown;
        }
        if(this.cooldown > 0) {
            this.cooldown -= board.changeTime;
        }

        this.setPosition();
    }

    loopLasersEnemies() { //Loops player lasers, removes them if off board, and removes enemies/lasers if hit
        for(let i = 0 ; i < this.lasers.length ; i++) {
            this.lasers[i].updateLaser();

            if(this.lasers[i].y < 0) {
                this.lasers[i].isDead = true;
                this.lasers[i].removeLaser();
            }
        }

        for(let i = 0 ; i < this.lasers.length ; i++) {
            const rect1 = this.lasers[i].laser.getBoundingClientRect();

            for(let j = 0 ; j < board.enemies.length ; j++) {
                if(!board.enemies[j].isDead) {
                    const rect2 = board.enemies[j].enemy.getBoundingClientRect();
                    if(rectIntersect(rect1, rect2)) {
                        this.lasers[i].isDead = true;
                        this.lasers[i].removeLaser();
                        board.enemies[j].isDead = true;
                        board.enemies[j].removeEnemy();
                        leaderboard.addScore(100);
                    }
                }
            }
        }

        for(let i = 0 ; i < this.lasers.length ; i++) {
            if(this.lasers[i].isDead === true) {
                this.lasers.splice(i, 1);
                i--;
            }
        }
        for(let i = 0 ; i < board.enemies.length ; i++) {
            if(board.enemies[i].isDead === true) {
                board.enemies.splice(i, 1);
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

class EnemyLaser {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.maxSpeed = 300; //Change to make faster/slower
        this.isDead = false; //Is off screen

        //Creates image of laser and puts it in position
        this.laser = document.createElement('img');
        this.laser.src = 'images/enemyLaser.png';
        this.laser.className = 'enemyLaser';
        board.link.appendChild(this.laser);
        this.setPosition();
    }

    setPosition() {
        this.laser.style.transform = `translate(${this.x}px, ${this.y}px)`; //CSS animation to move laser
    }
    updateLaser() {
        this.y += board.changeTime * this.maxSpeed;
        this.setPosition();
    }
    checkLaser() {
        if(this.y > board.height - board.enemyLaserHeight) {
            this.isDead = true;
            this.removeLaser();
        }
    }
    removeLaser() {
        board.link.removeChild(this.laser);
    }
}

class Enemy {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.isDead = false;
        this.cooldown = rand(0.5, 10); //Change these values to change enemy fire rate

        //Creates image of enemy and puts it in position
        this.enemy = document.createElement('img');
        this.enemy.src = 'images/enemy1.png';
        this.enemy.className = 'enemy';
        board.link.appendChild(this.enemy);
        this.setPosition();
    }

    setPosition() {
        this.enemy.style.transform = `translate(${this.x}px, ${this.y}px)`; //CSS animation to move laser
    }
    setPosition(changeX, changeY) {
        this.enemy.style.transform = `translate(${this.x + changeX}px, ${this.y + changeY}px)`; //CSS animation to move laser
    }
    removeEnemy() {
        board.link.removeChild(this.enemy);
    }
}

class Leaderboard{
    constructor(){
        this.score = 0;
        this.hiScore = 0;
    }
    addScore(tmpScore){
        this.score+=tmpScore;
    }
    update(){
        document.getElementById('score').innerHTML = this.score;
        const theScore = document.getElementById('score').innerHTML;
        document.getElementById('ldrBrdBtn0').value = theScore;
        document.getElementById('ldrBrdBtn1').value = theScore;
    }

}

function update() { //Updates board
    board.currentTime = Date.now();
    board.changeTime = (board.currentTime - board.pastTime) / 1000.0; //Prevents player movement depending on PC clock speed

    player.updatePlayer();
    player.loopLasersEnemies();
    board.updateEnemies();
    board.isLost = board.updateEnemyLasers();
    board.pastTime = board.currentTime;
    leaderboard.update();
    if(board.enemies.length === 0) {
        board.isWon = true;
    }

    if(board.isWon) {
        document.querySelector('#won').style.display = 'block';
    }
    else if(board.isLost) {
        board.updateLives();
        player.player.style.display = 'none';
        document.querySelector('#lost').style.display = 'block';
    }
    else if(board.lostLife) {
        player.player.style.display = 'none';
        player.reset();
        board.updateLives();
        board.lostLife = false;
        player.player.style.display = 'block';
        window.requestAnimationFrame(update); //Recursive
    }
    else {
        window.requestAnimationFrame(update); //Recursive
    }
}
function rectIntersect(r1, r2) { //Returns true if rectangles intersect
    return !(
        r2.left > r1.right ||
        r2.right < r1.left ||
        r2.top > r1.bottom ||
        r2.bottom < r1.top
    );
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
function rand(min, max) { //Built random function
  return min + Math.random() * (max - min);
}

//'Main' Starts Here

const board = new Board();
const player = new Player(board.getShipColor());
const leaderboard = new Leaderboard();

board.createEnemies();
window.addEventListener('keydown', onKeyDown);
window.addEventListener('keyup', onKeyUp);
window.requestAnimationFrame(update); //Calls the update function that updates the board
