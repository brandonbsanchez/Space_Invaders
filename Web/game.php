<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Space Invaders</title>
        <link href="styles.css" rel="stylesheet">
    </head>
    <body>
    
        <div id="container">
                <div id="leaderboard">
                    <h3>Score:</h3>
                    <h3 id="score">0</h3>
                </div>
            <div id="board"></div>
            <div id="lives">    
                <h1>Lives: <span id="livesLeft">3</span></h1>
            </div>
            <div id="won">
                <h1>Congratulations!</h1>
                <h2>You won.</h2>
                <br>
                <!-- <button onclick="window.location.reload()">Restart</button> -->
                <form method="POST" action="leaderboard.php">
                    <button id="ldrBrdBtn0" name="ldrBrdBtn0" type="submit" value=0>View Leaderboard</button>
                </form>
            </div>
            <div id="lost">
                <h1>Game over.</h1>
                <h2>You lost.</h2>
                <br>
                <form method="POST" action="leaderboard.php">
                    <button id="ldrBrdBtn1" name="ldrBrdBtn1" type="submit" value=0>View Leaderboard</button>
                </form>
            </div>
        </div>

        <script src="app.js"></script>

        <?php  
            session_start();

            $_SESSION['name'] = $_POST['name'];
            $_SESSION['shipColor'] = $_POST['shipType'];

            switch($_POST['shipType']){
                case "Blue":
                    $_SESSION['shipType'] = 1;
                    break;
                case "Green":
                    $_SESSION['shipType'] = 2;
                    break;
                case "Red":
                    $_SESSION['shipType'] = 3;
                    break;
                case "Yellow":
                    $_SESSION['shipType'] = 4;
                    break;
            }
        ?>
    </body>
</html>