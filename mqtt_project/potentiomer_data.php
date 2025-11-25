<!DOCTYPE html>
<html>
<head>
    <title>Potentiometer Data</title>
    <style>
            body {
                margin: 0;
                padding: 0;
                background-color: CadetBlue;
                font-family: Tahoma, Verdana, sans-serif;
            }
            header {
                width: 100%;
                margin: 0;
                background-color: DarkSlateGray;
                padding: 20px;
                color: white;
            }
            h1, h2 {
                margin: 0;
            }
            h3 {
                text-align: center;
            }
            a {
                color: DeepSkyBlue;
            }
            div {
                border-radius: 15px 50px;
                background-color: white;
                padding: 20px 20px 20px;
                width: 750px;
                margin: 20px auto;
            }
            #navbar {
              margin-top: 4px;
            }
            div iframe {
                display: block;
                vertical-align: top;
                width: 100%;
                border: 0;
            }
            p {
                text-align: center;
                color: white;
                font-weight: bold;
            }
            table {
                border-collapse: collapse;
                margin: 20px auto;
            }
            thead tr {
                background-color: DarkSlateGray;
                color: #ffffff;
                text-align: left;
                font-weight: bold;

            }
            th, td {
                padding: 12px 15px;
                text-align: left;
            }
            tbody tr {
                border-bottom: 1px solid #dddddd;
            }
            tbody tr:nth-of-type(odd){
                background-color: #DCDCDC;
            }
            tbody tr:nth-of-type(even){
                background-color: #f3f3f3f3;
            }
            tbody tr:last-of-type {
                border-bottom: 2px solid DarkSlateGray;
            }
    </style>
</head>

<body>

<header>
    <h1>Potentiometer Data Display</h1>
    <h2>MQTT Assignment</h2>
    <p>By: Anthony Meyer Slechta</p>
</header>
    <nav id="navbar"></nav>
    <script>
      fetch("navbar.html")
        .then(res => res.text())
        .then(html => document.getElementById("navbar").innerHTML = html)
        .catch(err => console.error("Navbar load failed:", err));
    </script>

<?php
$servername = "localhost";
$username = "u301268454_db_AnthonyMeye";
$password = "MyFirstDb2025!";
$dbname = "u301268454_AnthonyMeyer";

// Create DB connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("<p>Connection failed: " . $conn->connect_error . "</p>");
}

// Query potentiometer data
$sql = "SELECT pot_value, created_at 
        FROM potentiometer_data
        ORDER BY created_at DESC
        LIMIT 1000";   // limit for safety

$result = $conn->query($sql);
?>

<h3>Potentiometer Data Table</h3>

<table>
    <thead>
        <tr>
            <th>Date & Time</th>
            <th>Potentiometer Value</th>
        </tr>
    </thead>
    <tbody>
    <?php
    if ($result && $result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            echo "<tr>";
            echo "<td>" . $row["created_at"] . "</td>";
            echo "<td>" . number_format($row["pot_value"], 3) . "</td>";
            echo "</tr>";
        }
    } else {
        echo "<tr><td colspan='2'>No data available</td></tr>";
    }
    ?>
    </tbody>
</table>

<div>
    <iframe
      src="https://anthonymeyer.io/Chartjs1/graph.html"
      width="900"
      height="520"
      loading="lazy"
    ></iframe>
</div>

<?php $conn->close(); ?>

</body>
</html>
