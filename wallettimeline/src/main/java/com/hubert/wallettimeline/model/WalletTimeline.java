package com.hubert.wallettimeline.model;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class WalletTimeline {
    public static class AssetStat {
        private double value;
        private double income;

        public AssetStat(double value, double income) {
            this.value = value;
            this.income = income;
        }

        public AssetStat(AssetStat assetStat) {
            this(assetStat.getValue(), assetStat.getIncome());
        }

        public double getValue() {
            return value;
        }

        public double getIncome() {
            return income;
        }

        public void resetIncome() {
            income = 0;
        }
    }

    public static class WalletStat {
        private final LocalDate date;
        private final Map<String, AssetStat> assetsAndValues;

        public WalletStat(LocalDate date, Map<String, AssetStat> assetValues) {
            this.date = date;
            this.assetsAndValues = assetValues;
        }

        public Map<String, AssetStat> getAssetsAndValuesDeepCopy() {
            HashMap<String, AssetStat> copy = new HashMap<>();
            for (var assetAndValues : assetsAndValues.entrySet()) {
                copy.put(assetAndValues.getKey(), new AssetStat(assetAndValues.getValue()));
            }
            return copy;
        }

        public LocalDate getDate() {
            return date;
        }
    }

    private final List<WalletStat> walletStats;

    public WalletTimeline(List<WalletStat> walletStats) {
        this.walletStats = walletStats;
    }

    public List<WalletStat> getWalletStats() {
        return walletStats;
    }
}
