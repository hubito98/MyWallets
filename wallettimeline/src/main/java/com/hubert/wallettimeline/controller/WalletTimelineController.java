package com.hubert.wallettimeline.controller;

import com.hubert.wallettimeline.entity.Wallet;
import com.hubert.wallettimeline.model.WalletTimeline;
import com.hubert.wallettimeline.service.WalletTimelineService;
import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Optional;


@RestController
@RequestMapping(path = "wallet-timeline")
public class WalletTimelineController {

    private final WalletTimelineService walletTimelineService;

    public WalletTimelineController(WalletTimelineService walletTimelineService) {
        this.walletTimelineService = walletTimelineService;
    }

    @GetMapping(path = "{walletId}")
    public ResponseEntity<WalletTimeline> walletTimeline(@PathVariable int walletId) {
         Optional<WalletTimeline> walletTimeline = walletTimelineService.getWalletTimeline(walletId);
         HttpHeaders responseHeaders = new HttpHeaders();
         responseHeaders.set("Access-Control-Allow-Origin", "*");
         if (walletTimeline.isPresent()) {
             return ResponseEntity.ok()
                     .headers(responseHeaders)
                     .body(walletTimeline.get());
         }
         return ResponseEntity.notFound().headers(responseHeaders).build();
    }
}
