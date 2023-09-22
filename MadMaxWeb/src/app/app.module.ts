import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppComponent } from './app.component';
import { StatusComponent } from './status/status.component';
import { ControlComponent } from './control/control.component';
import { ErrorsComponent } from './errors/errors.component';
import { AutomaticComponent } from './control/automatic/automatic.component';
import { ManualComponent } from './control/manual/manual.component';
import { CommunicationService } from './shared/communication.service';

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
    HttpClientModule
  ],
  providers: [
    CommunicationService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
