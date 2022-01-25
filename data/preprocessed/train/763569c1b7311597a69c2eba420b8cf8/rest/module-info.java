module ro.mta.library_project {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires validatorfx;
    requires org.kordamp.ikonli.javafx;
    requires org.kordamp.bootstrapfx.core;
    requires eu.hansolo.tilesfx;
    requires java.net.http;
    requires com.google.common;
    requires java.sql;
    requires json.simple;
    requires pdfbox.app;
    requires java.security.sasl;
    requires java.desktop;
    requires com.fasterxml.jackson.core;
    requires com.fasterxml.jackson.databind;
    requires org.json;

    opens ro.mta.library_project to javafx.fxml;
    exports ro.mta.library_project;
    exports ro.mta.library_project.Controllers;
    opens ro.mta.library_project.Controllers to javafx.fxml;
    exports ro.mta.library_project.Controllers.LibrarianControllers;
    opens ro.mta.library_project.Controllers.LibrarianControllers to javafx.fxml;
    exports ro.mta.library_project.HelperClasses;
    opens ro.mta.library_project.HelperClasses to javafx.fxml;
    exports ro.mta.library_project.Models;
    opens ro.mta.library_project.Models to javafx.fxml;
    exports ro.mta.library_project.Controllers.AdminControllers;
    opens ro.mta.library_project.Controllers.AdminControllers to javafx.fxml;
}