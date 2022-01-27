package com.hubert.wallettimeline.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.List;

@Entity
@Table(name = "Wallets")
public class Wallet {
    @Id
    private int id;

    @Column(columnDefinition = "varchar(255)")
    private String name;

    @Column(columnDefinition = "varchar(255)")
    private String description;

    @Column(columnDefinition = "varchar(255)")
    private String userLogin;

    @OneToMany(targetEntity = Asset.class, mappedBy = "wallet")
    private List<Asset> assets;

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public String getUserLogin() {
        return userLogin;
    }

    public List<Asset> getAssets() { return assets; }
}
