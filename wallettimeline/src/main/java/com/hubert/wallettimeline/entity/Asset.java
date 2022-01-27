package com.hubert.wallettimeline.entity;

import javax.persistence.*;
import java.util.List;

@Entity
@Table(name = "Assets")
public class Asset {
    @Id
    private int id;

    @Column(columnDefinition = "varchar(255)")
    private String type;

    @Column(columnDefinition = "varchar(255)")
    private String description;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "walletId", referencedColumnName = "id")
    private Wallet wallet;

    @OneToMany(targetEntity = AssetState.class, mappedBy = "asset")
    private List<AssetState> assetStates;

    public int getId() {
        return id;
    }

    public String getType() {
        return type;
    }

    public String getDescription() {
        return description;
    }

    public List<AssetState> getAssetStates() { return assetStates; }
}
