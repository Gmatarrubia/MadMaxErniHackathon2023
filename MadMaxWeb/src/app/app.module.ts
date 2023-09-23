import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { RouterModule, Routes } from '@angular/router';
import { AngularFireModule } from '@angular/fire/compat';
import { AngularFireDatabaseModule } from '@angular/fire/compat/database';

import { AppComponent } from './app.component';
import { StatusComponent } from './status/status.component';
import { ControlComponent } from './control/control.component';
import { ErrorsComponent } from './errors/errors.component';
import { AutomaticComponent } from './control/automatic/automatic.component';
import { ManualComponent } from './control/manual/manual.component';
import { CommunicationService } from './shared/communication.service';
import { ControlService } from './control/control.service';

const routes: Routes = [
  { path: '', component: AutomaticComponent },
  { path: 'automatic', component: AutomaticComponent },
  { path: 'manual', component: ManualComponent }
];

const firebaseConfig = {
  apiKey: "AIzaSyB5xvigiAtF3JrdXaJ_hDU9QlTGgTj9nyk",
  authDomain: "mad-max-erni.firebaseapp.com",
  databaseURL: "https://mad-max-erni-default-rtdb.firebaseio.com",
  projectId: "mad-max-erni",
  storageBucket: "mad-max-erni.appspot.com",
  messagingSenderId: "93444458875",
  appId: "1:93444458875:web:3bded79b7823a044d155de"
};

@NgModule({
  declarations: [
    AppComponent,
    StatusComponent,
    ControlComponent,
    ErrorsComponent,
    AutomaticComponent,
    ManualComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule, 
    RouterModule.forRoot(routes),
    AngularFireModule.initializeApp(firebaseConfig),
    AngularFireDatabaseModule
  ],
  exports: [RouterModule],
  providers: [
    CommunicationService,
    ControlService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
