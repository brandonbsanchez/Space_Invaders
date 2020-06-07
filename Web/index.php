body {
    font-family: 'Aldrich';
    margin: 0;
    padding: 0;
    background-image: linear-gradient(rgb(46, 46, 46), white );
    background-repeat: no-repeat;
    color: black;
}
#Title{
    font-size: 30px;
    color: white;
}
#S {
    font-size: 20px;
}
#score {
    font-size: 20px;
    margin-left: 80px;
    margin-top: -22px;
    padding: 0; 
}
#container {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height:80vh;
}
#board {
    height: 600px;
    width: 800px;
    background-image: url(images/background.png);
    animation: scroll 15s linear infinite;
}
#leaderboard{
    color: white;
    background-color: black;
    height: 100px;
    width: 800px;
}
#player {
    position: absolute;
    width: 40px;
    margin-left: -20px; /*Moves center of object to middle*/
}
#lifeIcon{
    width: 25px;
    height: 25px;
}
.icon{
    width: 25px;
    height: 25px;
}
@keyframes scroll {
    from {background-position-y: 0px;}
    to {background-position-y: 1024px;}
}
.playerLaser {
    position: absolute;
    height: 20px;
    margin-left: -3.9001px;
}
.enemyLaser {
    position: absolute;
    height: 20px;
    margin-left: -10px;
}
.enemy {
    position: absolute;
    width: 40px;
    margin-left: -20px;
}
#won {
    display: none;
    position: absolute;
    background-color: rgb(17, 102, 14);
    text-align: center;
    border: solid 1px black;
    padding: 25px;
    border-radius: 30px;
}
#lost {
    display: none;
    position: absolute;
    background-color: #862828;
    text-align: center;
    border: solid 1px black;
    padding: 10px 50px;
    border-radius: 30px;
}
#won button, #lost button {
    padding: 10px;
    border-radius: 5px;
}
#lives {
    margin-left: -710px;
    font-size: 20px;
}
tr:nth-child(odd){background-color: rgb(107, 107, 107);}
tr:nth-child(even){background-color: rgb(153, 153, 153);}
