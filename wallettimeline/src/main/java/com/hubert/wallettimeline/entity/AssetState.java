package com.hubert.wallettimeline.entity;

import javax.persistence.*;
import java.time.LocalDate;

@Entity
@Table(name = "AssetStates")
public class AssetState {
    @Id
    private int id;

    private int year;
    private int month;
    private int day;
    private double value;
    private double income;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "assetId", referencedColumnName = "id")
    private Asset asset;

    public int getId() {
        return id;
    }

    public int getYear() {
        return year;
    }

    public int getMonth() {
        return month;
    }

    public int getDay() {
        return day;
    }

    public double getValue() {
        return value;
    }

    public double getIncome() {
        return income;
    }

    public LocalDate getDate() {
        return LocalDate.of(year, month, day);
    }
}
