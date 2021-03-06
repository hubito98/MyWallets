package com.hubert.wallettimeline.service;

import com.hubert.wallettimeline.entity.Asset;
import com.hubert.wallettimeline.entity.AssetState;
import com.hubert.wallettimeline.entity.Wallet;
import com.hubert.wallettimeline.model.WalletTimeline;
import com.hubert.wallettimeline.repository.WalletRepository;
import org.springframework.data.util.Pair;
import org.springframework.stereotype.Service;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

@Service
public class WalletTimelineService {

    private final WalletRepository walletRepository;

    public WalletTimelineService(WalletRepository walletRepository) {
        this.walletRepository = walletRepository;
    }

    public Optional<WalletTimeline> getWalletTimeline(int walletId) {
        Optional<Wallet> wallet = walletRepository.findById(walletId);
        if (wallet.isEmpty()) {
            return Optional.empty();
        }
        List<Asset> walletAssets = wallet.get().getAssets();
        Map<LocalDate, List<Pair<String, AssetState>>> dateToAssetStates = walletAssets.stream()
                .flatMap(asset -> asset.getAssetStates().stream()
                        .map(state -> Pair.of(asset.getType(), state)))
                .collect(Collectors.groupingBy(pair -> pair.getSecond().getDate(), TreeMap::new, Collectors.toList()));
        List<WalletTimeline.WalletStat> walletStats = new ArrayList<>();
        for (var dateAndAssetStates : dateToAssetStates.entrySet()) {
            LocalDate date = dateAndAssetStates.getKey();
            Map<String, WalletTimeline.AssetStat> assetsAndValues;
            if (walletStats.isEmpty()) {
                assetsAndValues = new HashMap<>();
            } else {
                 // if at some time t1 there is no update on some assets that are already in wallet
                 // use their last known values (no last known incomes)
                assetsAndValues = walletStats.get(walletStats.size()-1).getAssetsAndValuesDeepCopy();
                for (var assetAndValues : assetsAndValues.values()) {
                    assetAndValues.resetIncome();
                }
            }
            for (Pair<String, AssetState> state : dateAndAssetStates.getValue()) {
                assetsAndValues.put(state.getFirst(),
                        new WalletTimeline.AssetStat(state.getSecond().getValue(), state.getSecond().getIncome()));
            }
            walletStats.add(new WalletTimeline.WalletStat(date, assetsAndValues));
        }
        return Optional.of(new WalletTimeline(walletStats));
    }
}
