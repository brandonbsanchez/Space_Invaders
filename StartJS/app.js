class Board {
    constructor() {
        this.height = 600;
        this.width = 800;
        this.link = document.querySelector('#board');
    }
}

class Player {
    constructor(board) {
        this.x = board.width / 2;
        this.y = board.height - 60;
        this.width = 20;
        this.player = document.createElement('img');
        this.player.src = 'images/player.png';
        this.player.id = 'player';
        board.link.appendChild(this.player);
        this.setPosition();
    }

    setPosition() {
        this.player.style.transform = `translate(${this.x}px, ${this.y}px)`;
    }
}

const board = new Board();

console.log(board);
const player = new Player(board);


window.addEventListener('keydown', function(e) {updateCoord(e, player, board);});
window.addEventListener('keyup', function(e) {updateCoord(e, player, board);});

function updateCoord(event, player, board){
    if(event.key === 'd') {
        player.x += 10;
    }
    else if(event.key ==='a') {
        player.x -= 10;
    }

    if(player.x < player.width) {
        player.x = player.width;
    }
    else if(player.x > board.width - player.width) {
        player.x = board.width - player.width;
    }

    player.setPosition();
}