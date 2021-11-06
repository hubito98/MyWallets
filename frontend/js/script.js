let restAddress = "http://localhost:8080"

$(document).ready(function(){
    loadUsersMenu();
});

// users menu

function loadUsersMenu() {
    clear();
    prepareTableForUsers();
    $.ajax({
        url: restAddress + "/users"
    }).then(function(data) {
        usersJSON = jQuery.parseJSON(data);
        addUsersToTable(usersJSON);
    });
}

function prepareTableForUsers() {
    prepareTable();
    var headRow = $("<tr><th scope=\"col\">User</th><th scope=\"col\">Actions</th></tr>")
    $("#menu table thead").append(headRow);
}

function addUsersToTable(usersJSON) {
    var users = usersJSON.users;
    users.forEach(addUserTableRow);
}

function addUserTableRow(user) {
    var loginCell = $("<td></td>").text(user.login);
    var detailsButton = $("<button></button>")
            .attr("type", "button")
            .attr("class", "btn btn-light btn-sm")
            .attr("onclick", "loadUserDetails(\"" + user.login + "\")")
            .text("Details");
    var actionsCell = $("<td></td>").append(detailsButton);
    var tr = $("<tr></tr>").append(loginCell, actionsCell);
    $("#menu table tbody").append(tr);
}

// user details

function loadUserDetails(login) {
    clear();
    $.ajax({
        url: restAddress + "/users/" + login
    }).then(function(data) {
        userJSON = jQuery.parseJSON(data);
        addUserInfo(userJSON.user);
        prepareTableForWallets();
        addWalletsToTable(userJSON.wallets);
    });
}

function addUserInfo(user) {
    var login = user.login;
    var header = $("<h3></h3>")
            .text(login + " wallets");
    $("#menu").append(header);
}

function prepareTableForWallets() {
    prepareTable();
    var headRow = $("<tr><th scope=\"col\">Name</th><th scope=\"col\">Description</th><th scope=\"col\">Actions</th></tr>")
    $("#menu table thead").append(headRow);
}

function addWalletsToTable(wallets) {
    wallets.forEach(function (wallet) {
        var nameCell = $("<td></td>")
                .text(wallet.name);
        var descriptionCell = $("<td></td>")
                .text(wallet.description);
        var statsButton = $("<button></button>")
                .attr("type", "button")
                .attr("class", "btn btn-light btn-sm")
                .attr("onclick", "loadWalletStatistics(" + wallet.id + ")")
                .text("Statistics");
        var detailsButton = $("<button></button>")
                .attr("type", "button")
                .attr("class", "btn btn-light btn-sm")
                .attr("onclick", "loadWalletDetails(" + wallet.id + ")")
                .text("Details");
        var actionsCell = $("<td></td>").append(statsButton, detailsButton);
        var tr = $("<tr></tr>").append(nameCell, descriptionCell, actionsCell);
        $("#menu table tbody").append(tr);
    });
}

// wallet statistics

function loadWalletStatistics(walletId) {
    $.ajax({
        url: restAddress + "/wallet-statistics/" + walletId
    }).then(function(data) {
        statsJSON = jQuery.parseJSON(data).basicWalletStatistics;
        clearContent();
        addWalletStatsOverallInfo(statsJSON.walletName, statsJSON.wholeWalletValue);
        addPieChart(statsJSON.assetStats);
    });
}

function addWalletStatsOverallInfo(walletName, wholeWalletValue) {
    var header = $("<h4></h4>")
            .text(walletName + " statistics");
    var walletInfo = $("<p></p>")
            .text("Wallet value: " + wholeWalletValue);
    $("#content").append(header, walletInfo);
}

function addPieChart(assetStats) {
    var assetTypes = [];
    var assetValues = [];
    var colors = [];

    assetStats.forEach(function (assetStat) {
        assetTypes.push(assetStat.type + "(" + assetStat.percentageOfTotal + "%)");
        assetValues.push(assetStat.currentValue);
        colors.push('#'+Math.floor(Math.random()*16777215).toString(16));
    });

    var canvas = $("<div style=\"width: 70%; margin-left: auto; margin-right: auto;\"><canvas id=\"asset-stats-pie-chart\"></canvas></div>");
    $("#content").append(canvas);
    var ctxP = document.getElementById("asset-stats-pie-chart").getContext("2d");
    new Chart(ctxP, {
        type: 'pie',
        data: {
          labels: assetTypes,
          datasets: [{
            data: assetValues,
            backgroundColor: colors,
          }]
        },
        options: {
          responsive: true
        }
      });
}

// wallet details

function loadWalletDetails(walletId) {
    clear();
    $("#menu").text("wallet details will be here");
}

// utils

function clear() {
    clearMenu();
    clearContent();
}

function clearMenu() {
    $("#menu").empty();
}

function clearContent() {
    $("#content").empty();
}

function prepareTable() {
    var table = $("<table></table>")
            .attr("class", "table table-hover");
    var thead = $("<thead></thead>");
    var tbody = $("<tbody></tbody>");
    table.append(thead, tbody);
    $("#menu").append(table);
}
