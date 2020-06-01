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
                <button onclick="window.location.reload()">Restart</button>
            </div>
            <div id="lost">
                <h1>Game over.</h1>
                <h2>You lost.</h2>
                <br>
                <!-- <button onclick="window.location.reload()">Restart</button> -->
                <form method="POST" action="leaderboard.php">
                    <button type="submit" value=0>View Leaderboard</button>
                </form>
            </div>
        </div>

        <script src="app.js"></script>

        <!-- <?php
            $servername = "209.129.8.7";
            $username = "RCCCSCCIS17B";
            $password = "4050240368";
            $dbname = "RCCCSCCIS17B";

            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            } 

            // Query the Database
            $sql = "SELECT `spaceinvaders_entity_player`.`name` AS `Player Name`, `spaceinvaders_enum_color`.`what_color` 
            AS `Ship Color`, `spaceinvaders_entity_highscore`.`highscore` AS `High Score` 
            FROM `RCCCSCCIS17B`.`spaceinvaders_xref_plyr_ship_highscore` AS `spaceinvaders_xref_plyr_ship_highscore`, `RCCCSCCIS17B`.`spaceinvaders_entity_player` 
            AS `spaceinvaders_entity_player`, `RCCCSCCIS17B`.`spaceinvaders_entity_ship` 
            AS `spaceinvaders_entity_ship`, `RCCCSCCIS17B`.`spaceinvaders_entity_highscore` 
            AS `spaceinvaders_entity_highscore`, `RCCCSCCIS17B`.`spaceinvaders_enum_color` AS `spaceinvaders_enum_color` 
            WHERE `spaceinvaders_xref_plyr_ship_highscore`.`plyr_id` = `spaceinvaders_entity_player`.`plyr_id` 
            AND `spaceinvaders_xref_plyr_ship_highscore`.`ship_id` = `spaceinvaders_entity_ship`.`ship_id` 
            AND `spaceinvaders_xref_plyr_ship_highscore`.`highscore_id` = `spaceinvaders_entity_highscore`.`highscore_id` 
            AND `spaceinvaders_entity_ship`.`id_color` = `spaceinvaders_enum_color`.`id_ship` ORDER BY `High Score` DESC";

            $result = $conn->query($sql);

            echo "<table border='1'>";
                echo "<tr>";
                    echo "<th>".'Rank'."</th>";
                    echo "<th>".'Player Name'."</th>";
                    echo "<th>".'Ship Color'."</th>";
                    echo "<th>".'High Score'."</th>";
                echo "</tr>";

            if ($result->num_rows > 0) 
            {
                $rank = 1;
                // output data of each row
                while($re = $result->fetch_assoc()) {
                    echo "<tr>";
                        echo "<td>".$rank."</td>";
                        echo "<td>".$re["Player Name"]."</td>";
                        echo "<td>".$re["Ship Color"]."</td>";
                        echo "<td>".$re["High Score"]."</td>";
                    echo "</tr>";
                    $rank++;
                }
            } else {
                echo "0 results";
            }
            echo "</table>";

            $conn->close();
        ?> -->

    </body>
</html>
