import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { RouterModule, Routes } from '@angular/router';

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
    RouterModule.forRoot(routes)
  ],
  exports: [RouterModule],
  providers: [
    CommunicationService,
    ControlService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
