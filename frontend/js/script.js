let restAddress = "http://localhost:8080";
let colorsPalette = ["#fd7f6f", "#7eb0d5", "#b2e061", "#bd7ebe", "#ffb55a", "#ffee65", "#beb9db", "#fdcce5", "#8bd3c7"];

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
    prepareUserForm();
}

function prepareTableForUsers() {
    prepareTable();
    var headRow = $("<tr><th scope=\"col\">Login</th><th scope=\"col\"></th></tr>")
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
            .text("Szczegóły");
    var actionsCell = $("<td></td>").append(detailsButton);
    var tr = $("<tr></tr>").append(loginCell, actionsCell);
    $("#menu table tbody").append(tr);
}

function prepareUserForm() {
    prepareForm();
    var loginLabel = $("<label></label>")
            .text("Login:")
            .attr("for", "user-login")
            .attr("class", "form-label");
    var loginInput = $("<input>")
            .attr("type", "text")
            .attr("class", "form-control")
            .attr("id", "user-login");
    var loginDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(loginLabel, loginInput);
    var submitButton = $("<button></button>")
            .attr("class", "btn btn-primary")
            .attr("type", "button")
            .attr("onclick", "addUser()")
            .text("Dodaj użytkownika");
    $("#form form").append(loginDiv, submitButton);
}

// add user

function addUser() {
    var login = $.trim($("#user-login").val());
    if (login.length != 0) {
        var inputJson = {"login": login};
        $.ajax({
            url: restAddress + "/users/",
            type: 'POST',
            data: JSON.stringify(inputJson)
        }).then(function(data) {
            loadUsersMenu();
        });
    }
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
        setId(login);
    });
    prepareWalletForm();
}

function addUserInfo(user) {
    var login = user.login;
    var header = $("<h3></h3>")
            .text(login);
    $("#menu").append(header);
}

function prepareTableForWallets() {
    prepareTable();
    var headRow = $("<tr><th scope=\"col\">Nazwa</th><th scope=\"col\">Opis</th><th scope=\"col\"></th></tr>")
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
                .text("Stats");
        var detailsButton = $("<button></button>")
                .attr("type", "button")
                .attr("class", "btn btn-light btn-sm")
                .attr("onclick", "loadWalletDetails(" + wallet.id + ")")
                .text("Szczegóły");
        var actionsCell = $("<td></td>").append(statsButton, detailsButton);
        var tr = $("<tr></tr>").append(nameCell, descriptionCell, actionsCell);
        $("#menu table tbody").append(tr);
    });
}

function prepareWalletForm() {
    prepareForm();
    var nameLabel = $("<label></label>")
            .text("Nazwa portfela:")
            .attr("for", "wallet-name")
            .attr("class", "form-label");
    var nameInput = $("<input>")
            .attr("type", "text")
            .attr("class", "form-control")
            .attr("id", "wallet-name");
    var nameDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(nameLabel, nameInput);
    var descriptionLabel = $("<label></label>")
            .text("Opis portfela:")
            .attr("for", "wallet-description")
            .attr("class", "form-label");
    var descriptionInput = $("<input>")
            .attr("type", "text")
            .attr("class", "form-control")
            .attr("id", "wallet-description");
    var descriptionDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(descriptionLabel, descriptionInput);
    var submitButton = $("<button></button>")
            .attr("class", "btn btn-primary")
            .attr("type", "button")
            .attr("onclick", "addWallet()")
            .text("Dodaj portfel");
    $("#form form").append(nameDiv, descriptionDiv, submitButton);
}

// add wallet

function addWallet() {
    var name = $.trim($("#wallet-name").val());
    var description = $.trim($("#wallet-description").val());
    if (name.length != 0) {
        var inputJson = {"name": name, "description": description, "userLogin": getId()};
        $.ajax({
            url: restAddress + "/wallets/",
            type: 'POST',
            data: JSON.stringify(inputJson)
        }).then(function(data) {
            loadUserDetails(getId());
        });
    }
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
            .text("Wartość portfela: " + currencyFormat(wholeWalletValue));
    $("#content").append(header, walletInfo);
}

function addWalletChart(assetStats) {
    var assetTypes = [];
    var assetValues = [];
    var colors = [];

    for (var i = 0; i < assetStats.length; i++) {
        let assetStat = assetStats[i];
        assetTypes.push(assetStat.type + " - " + currencyFormat(assetStat.currentValue) +
                " (" + percentFormat(assetStat.percentageOfTotal) +")");
        assetValues.push(assetStat.currentValue);
        colors.push(chooseColor(i));
    }

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
            plugins: {
                tooltip: {
                    callbacks: {
                        label: function(context) {
                            return context.label;
                        }
                    }
                }
            },
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
        setId(walletId);
    });
    prepareAssetForm();
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
    var headRow = $("<tr><th scope=\"col\">Typ</th><th scope=\"col\">Opis</th><th scope=\"col\"></th></tr>")
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
                .text("Stats");
        var detailsButton = $("<button></button>")
                .attr("type", "button")
                .attr("class", "btn btn-light btn-sm")
                .attr("onclick", "loadAssetDetails(" + asset.id + ")")
                .text("Szczegóły");
        var actionsCell = $("<td></td>").append(statsButton, detailsButton);
        var tr = $("<tr></tr>").append(typeCell, descriptionCell, actionsCell);
        $("#menu table tbody").append(tr);
    });
}

function prepareAssetForm() {
    prepareForm();
    var typeLabel = $("<label></label>")
            .text("Typ aktywa:")
            .attr("for", "asset-type")
            .attr("class", "form-label");
    var typeInput = $("<input>")
            .attr("type", "text")
            .attr("class", "form-control")
            .attr("id", "asset-type");
    var typeDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(typeLabel, typeInput);
    var descriptionLabel = $("<label></label>")
            .text("Opis aktywa:")
            .attr("for", "asset-description")
            .attr("class", "form-label");
    var descriptionInput = $("<input>")
            .attr("type", "text")
            .attr("class", "form-control")
            .attr("id", "asset-description");
    var descriptionDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(descriptionLabel, descriptionInput);
    var submitButton = $("<button></button>")
            .attr("class", "btn btn-primary")
            .attr("type", "button")
            .attr("onclick", "addAsset()")
            .text("Dodaj aktywo");
    $("#form form").append(typeDiv, descriptionDiv, submitButton);
}

// add asset

function addAsset() {
    var type = $.trim($("#asset-type").val());
    var description = $.trim($("#asset-description").val());
    if (type.length != 0) {
        var inputJson = {"type": type, "description": description,
                         "walletId": parseInt(getId())};
        $.ajax({
            url: restAddress + "/assets/",
            type: 'POST',
            data: JSON.stringify(inputJson)
        }).then(function(data) {
            loadWalletDetails(parseInt(getId()));
        });
    }
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
        addAssetStatesStatsTable(statsJSON.basicAssetStatistics.assetStateStats);
    });
}

function addAssetStatsOverallInfo(assetType, newestAssetValue, sumOfIncomes) {
    var header = $("<h4></h4>")
            .text(assetType);
    var assetValue = $("<p></p>")
            .text("Wartość aktywa: " + currencyFormat(newestAssetValue));
    var assetIncomes = $("<p></p>")
            .text("Suma wpłat: " + currencyFormat(sumOfIncomes));
    let growth = newestAssetValue - sumOfIncomes;
    let isGrowthNegative = growth < 0;
    var assetGrowth = $("<p></p>")
            .attr("class", `text-${isGrowthNegative ? "danger" : "success"}`)
            .text(`Zysk: ${currencyFormat(growth)}
                  (${newestAssetValue != 0 ? percentFormat(growth / newestAssetValue * 100) : percentFormat(0)})`)
    $("#content").append(header, assetValue, assetIncomes, assetGrowth);
}

function addAssetChart(assetStatesStats) {
    var growths = [];
    var growthsInPercent = [];
    var growthsInPercentScaledByYear = [];
    var values = [];
    var incomes = [];
    var labels = [];
    assetStatesStats.slice().reverse().forEach(function(assetStateStat) {
        growths.push(assetStateStat.growth);
        values.push(assetStateStat.value);
        incomes.push(assetStateStat.income);
        growthsInPercent.push(assetStateStat.growthInPercent);
        growthsInPercentScaledByYear.push(assetStateStat.growthInPercentScaledByYear);
        const date = assetStateStat.date;
        labels.push(dateFormat(date.day, date.month, date.year));
    });

    var canvas = $("<div style=\"width: 100%; margin-left: auto; margin-right: auto;\"><canvas id=\"asset-states-stats-stacked-chart\"></canvas></div>");
    $("#content").append(canvas);
    var ctxP = document.getElementById("asset-states-stats-stacked-chart").getContext("2d");
    const data = {
        labels: labels,
        datasets: [
            {
                label: 'wartość',
                data: values,
                backgroundColor: chooseColor(0),
                hidden: false
            },
            {
                label: 'wpłata',
                data: incomes,
                backgroundColor: chooseColor(1),
                hidden: true
            },
            {
                label: 'zysk',
                data: growths,
                backgroundColor: chooseColor(2),
                hidden: true
            },
            {
                label: '% zysk',
                data: growthsInPercent,
                backgroundColor: chooseColor(3),
                hidden: true
            },
            {
                label: '% zysk roczny',
                data: growthsInPercentScaledByYear,
                backgroundColor: chooseColor(4),
                hidden: true
            },
            ]
    };
    const config = {
        type: 'bar',
        data: data,
        options: {
            plugins: {
                tooltip: {
                    callbacks: {
                        label: function(context) {
                            let rawValue = context.raw;
                            // values in percent ("growth in percent" or "growth in percent scaled by year")
                            if (context.datasetIndex == 3 || context.datasetIndex == 4) {
                                return percentFormat(rawValue);
                            } else {
                                return currencyFormat(rawValue);
                            }
                        },
                        title: function(context) {
                            return context[0].dataset.label;
                        }
                    }
                }
            },
            responsive: true,
        }
      };
    new Chart(ctxP, config);
}

function addAssetStatesStatsTable(assetStatesStats) {
    prepareTableForAssetStatesStats();
    addAssetStatesStatsToTable(assetStatesStats);
}

function prepareTableForAssetStatesStats() {
    var table = $("<table></table>")
            .attr("class", "table");
    var thead = $("<thead></thead>");
    var tbody = $("<tbody></tbody>");
    table.append(thead, tbody);
    $("#content").append(table);
    var headRow = $("<tr><th scope=\"col\">Data</th><th scope=\"col\">Wartość</th><th scope=\"col\">Wpłata</th><th scope=\"col\">Zysk</th><th scope=\"col\">Zysk roczny</th></tr>")
    $("#content table thead").append(headRow);
}

function addAssetStatesStatsToTable(assetStatesStats) {
    assetStatesStats.forEach(function (assetStateStat) {
        var dateCell = $("<td></td>")
                .text(dateFormat(assetStateStat.date.day, assetStateStat.date.month, assetStateStat.date.year));
        var valueCell = $("<td></td>")
                .text(currencyFormat(assetStateStat.value));
        var incomeCell = $("<td></td>")
                .text(currencyFormat(assetStateStat.income));
        var growthCell = $("<td></td>")
                .text(`${currencyFormat(assetStateStat.growth)} (${percentFormat(assetStateStat.growthInPercent)})`);
        var growthByYearCell = $("<td></td>")
                .text(percentFormat(assetStateStat.growthInPercentScaledByYear));
        let isGrowthNegative = assetStateStat.growth < 0;
        var tr = $("<tr></tr>")
                .attr("class", `table-${isGrowthNegative ? "danger" : "success"}`)
                .append(dateCell, valueCell, incomeCell, growthCell, growthByYearCell);
        $("#content table tbody").append(tr);
    });
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
        setId(assetId);
    });
    prepareAssetStateForm();
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
    var headRow = $("<tr><th scope=\"col\">Data</th><th scope=\"col\">Wartość</th><th scope=\"col\">Wpłata</th><th scope=\"col\"></th></tr>")
    $("#menu table thead").append(headRow);
}

function addAssetStatesToTable(assetStates) {
    assetStates.forEach(function (assetState) {
        var dateCell = $("<td></td>")
                .text(dateFormat(assetState.date.day, assetState.date.month, assetState.date.year));
        var valueCell = $("<td></td>")
                .text(currencyFormat(assetState.value));
        var incomeCell = $("<td></td>")
                .text(currencyFormat(assetState.income));
        var removeButton = $("<button></button>")
                .attr("type", "button")
                .attr("class", "btn btn-danger btn-sm")
                .attr("onclick", "removeAssetState(" + assetState.id + ")")
                .text("X");
        var actionsCell = $("<td></td>").append(removeButton);
        var tr = $("<tr></tr>").append(dateCell, valueCell, incomeCell, actionsCell);
        $("#menu table tbody").append(tr);
    });
}

function removeAssetState(id) {
    if (confirm('Na pewno chcesz to usunąć?')) {
        $.ajax({
            url: restAddress + "/asset-states/" + id,
            type: 'POST'
        }).then(function(data) {
            loadAssetDetails(parseInt(getId()));
        });
    }
}

function prepareAssetStateForm() {
    prepareForm();
    var dateLabel = $("<label></label>")
            .text("Data stanu:")
            .attr("for", "asset-state-date")
            .attr("class", "form-label");
    var dateInput = $("<input>")
            .attr("type", "date")
            .attr("class", "form-control")
            .attr("id", "asset-state-date");
    var dateDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(dateLabel, dateInput);
    var valueLabel = $("<label></label>")
            .text("Wartość aktywa po wpłacie:")
            .attr("for", "asset-state-value")
            .attr("class", "form-label");
    var valueInput = $("<input>")
            .attr("type", "number")
            .attr("class", "form-control")
            .attr("id", "asset-state-value");
    var valueDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(valueLabel, valueInput);
    var incomeLabel = $("<label></label>")
            .text("Wpłata:")
            .attr("for", "asset-state-income")
            .attr("class", "form-label");
    var incomeInput = $("<input>")
            .attr("type", "number")
            .attr("class", "form-control")
            .attr("id", "asset-state-income")
    var incomeDiv = $("<div></div>")
            .attr("class", "mb-3")
            .append(incomeLabel, incomeInput);
    var submitButton = $("<button></button>")
            .attr("class", "btn btn-primary")
            .attr("type", "button")
            .attr("onclick", "addAssetState()")
            .text("Dodaj stan aktywa");
    $("#form form").append(dateDiv, incomeDiv, valueDiv, submitButton);
}

// add asset state

function addAssetState() {
    var dateInput = $.trim($("#asset-state-date").val());
    var valueInput = $.trim($("#asset-state-value").val());
    var incomeInput = $.trim($("#asset-state-income").val());
    if (dateInput.length != 0 && valueInput.length != 0
            && incomeInput.length != 0) {
        var date = new Date(dateInput);
        var value = parseFloat(valueInput);
        var income = parseFloat(incomeInput);
        var year = date.getFullYear();
        var month = date.getMonth() + 1;
        var day = date.getDate();
        var assetId = parseInt(getId());
        var inputJson = {"date": {"year": year, "month": month, "day": day},
                         "value": value, "income": income, "assetId": assetId};
        $.ajax({
            url: restAddress + "/asset-states/",
            type: 'POST',
            data: JSON.stringify(inputJson)
        }).then(function(data) {
            loadAssetDetails(assetId);
        });
    }
}


// utils

function clear() {
    clearMenu();
    clearContent();
    clearForm();
    setId("");
}

function clearMenu() {
    $("#menu").empty();
}

function clearContent() {
    $("#content").empty();
}

function clearForm() {
    $("#form").empty();
}

function prepareTable() {
    var table = $("<table></table>")
            .attr("class", "table table-hover");
    var thead = $("<thead></thead>");
    var tbody = $("<tbody></tbody>");
    table.append(thead, tbody);
    $("#menu").append(table);
}

function prepareForm() {
    var form = $("<form></form>")
            .attr("style", ";width: 80%; margin-left: auto; margin-right: auto; margin-top: 100px;");
    $("#form").append(form);
}

function setId(id) {
    $("#id").text(id);
}

function getId() {
    return $("#id").text();
}

function chooseColor(i) {
    return colorsPalette[i % colorsPalette.length];
}

function currencyFormat(amount) {
    return Number(amount).toLocaleString('pl-PL', { style: 'currency', currency: 'PLN' })
}

function percentFormat(percent) {
    return Number(percent/100).toLocaleString('pl-PL', {style: 'percent', maximumFractionDigits: 2})
}

function dateFormat(day, month, year) {
    return `${day}/${month}/${year}`;
}
