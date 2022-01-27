package com.hubert.wallettimeline.model;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class WalletTimeline {
    public static class WalletStat {
        private final LocalDate date;
        private final Map<String, Double> assetsAndValues;

        public WalletStat(LocalDate date, Map<String, Double> assetValues) {
            this.date = date;
            this.assetsAndValues = assetValues;
        }

        public Map<String, Double> getAssetsAndValues() {
            return new HashMap<>(assetsAndValues);
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
