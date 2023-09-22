import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { StatusComponent } from './status/status.component';
import { ControlComponent } from './control/control.component';
import { ErrorsComponent } from './errors/errors.component';
import { AutomaticComponent } from './control/automatic/automatic.component';
import { ManualComponent } from './control/manual/manual.component';

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
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
