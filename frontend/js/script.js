let restAddress = "http://localhost:8080"

$(document).ready(function(){
    loadUsersMenu();
});

// users menu

function loadUsersMenu() {
    clear();
    prepareTableForUsers();
    $.ajax({
        url: restAddress + "/users",
        type: 'GET',
        datatype: 'json'
    }).then(function(usersJSON) {
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
        url: restAddress + "/users/" + login,
        type: 'GET',
        datatype: 'json'
    }).then(function(userJSON) {
        addUserInfo(userJSON.user);
        prepareTableForWallets();
        addWalletsToTable(userJSON.wallets);
    });
}

function addUserInfo(user) {
    var login = user.login;
    var header = $("<h3></h3>")
            .text(login);
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
        url: restAddress + "/wallet-statistics/" + walletId,
        type: 'GET',
        datatype: 'json'
    }).then(function(statsJSON) {
        clearContent();
        addWalletStatsOverallInfo(statsJSON.basicWalletStatistics.walletName, statsJSON.basicWalletStatistics.wholeWalletValue);
        addWalletChart(statsJSON.basicWalletStatistics.assetStats);
    });
}

function addWalletStatsOverallInfo(walletName, wholeWalletValue) {
    var header = $("<h4></h4>")
            .text(walletName);
    var walletInfo = $("<p></p>")
            .text("Wallet value: " + wholeWalletValue);
    $("#content").append(header, walletInfo);
}

function addWalletChart(assetStats) {
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
    $.ajax({
        url: restAddress + "/wallets/" + walletId,
        type: 'GET',
        datatype: 'json'
    }).then(function(walletJSON) {
        addWalletInfo(walletJSON.wallet);
        prepareTableForAssets();
        addAssetsToTable(walletJSON.assets);
    });
}

function addWalletInfo(wallet) {
    var name = wallet.name;
    var description = wallet.description;
    var header = $("<h3></h3>")
            .text(name);
    var descriptionParagraph = $("<p></p>")
            .text(description);
    $("#menu").append(header, descriptionParagraph);
}

function prepareTableForAssets() {
    prepareTable();
    var headRow = $("<tr><th scope=\"col\">Type</th><th scope=\"col\">Description</th><th scope=\"col\">Actions</th></tr>")
    $("#menu table thead").append(headRow);
}

function addAssetsToTable(assets) {
    assets.forEach(function (asset) {
        var typeCell = $("<td></td>")
                .text(asset.type);
        var descriptionCell = $("<td></td>")
                .text(asset.description);
        var statsButton = $("<button></button>")
                .attr("type", "button")
                .attr("class", "btn btn-light btn-sm")
                .attr("onclick", "loadAssetStatistics(" + asset.id + ")")
                .text("Statistics");
        var detailsButton = $("<button></button>")
                .attr("type", "button")
                .attr("class", "btn btn-light btn-sm")
                .attr("onclick", "loadAssetDetails(" + asset.id + ")")
                .text("Details");
        var actionsCell = $("<td></td>").append(statsButton, detailsButton);
        var tr = $("<tr></tr>").append(typeCell, descriptionCell, actionsCell);
        $("#menu table tbody").append(tr);
    });
}

// asset statistics

function loadAssetStatistics(assetId) {
    $.ajax({
        url: restAddress + "/asset-statistics/" + assetId,
        type: 'GET',
        datatype: 'json'
    }).then(function(statsJSON) {
        clearContent();
        addAssetStatsOverallInfo(statsJSON.basicAssetStatistics.assetType,
                                 statsJSON.basicAssetStatistics.newestAssetValue,
                                 statsJSON.basicAssetStatistics.sumOfIncomes);
        addAssetChart(statsJSON.basicAssetStatistics.assetStateStats);
    });
}

function addAssetStatsOverallInfo(assetType, newestAssetValue, sumOfIncomes) {
    var header = $("<h4></h4>")
            .text(assetType);
    var assetValue = $("<p></p>")
            .text("Asset value: " + newestAssetValue);
    var assetIncomes = $("<p></p>")
            .text("Sum of incomes: " + sumOfIncomes);
    $("#content").append(header, assetValue, assetIncomes);
}

function addAssetChart(assetStateStats) {
    $("#content").append(JSON.stringify(assetStateStats));
}

// asset details

function loadAssetDetails(assetId) {
    clear();
    $.ajax({
        url: restAddress + "/assets/" + assetId,
        type: 'GET',
        datatype: 'json'
    }).then(function(assetJSON) {
        addAssetInfo(assetJSON.asset)
        prepareTableForAssetStates();
        addAssetStatesToTable(assetJSON.assetStates);
    });
}

function addAssetInfo(asset) {
    var type = asset.type;
    var description = asset.description;
    var header = $("<h3></h3>")
            .text(type);
    var descriptionParagraph = $("<p></p>")
            .text(description);
    $("#menu").append(header, descriptionParagraph);
}

function prepareTableForAssetStates() {
    prepareTable();
    var headRow = $("<tr><th scope=\"col\">Date</th><th scope=\"col\">Value</th><th scope=\"col\">Income</th><th scope=\"col\">Actions</th></tr>")
    $("#menu table thead").append(headRow);
}

function addAssetStatesToTable(assetStates) {
    assetStates.forEach(function (assetState) {
        var dateCell = $("<td></td>")
                .text(assetState.date.day + "-" + assetState.date.month + "-" + assetState.date.year);
        var valueCell = $("<td></td>")
                .text(assetState.value);
        var incomeCell = $("<td></td>")
                .text(assetState.income);
        var actionsCell = $("<td></td>");
        var tr = $("<tr></tr>").append(dateCell, valueCell, incomeCell, actionsCell);
        $("#menu table tbody").append(tr);
    });
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
