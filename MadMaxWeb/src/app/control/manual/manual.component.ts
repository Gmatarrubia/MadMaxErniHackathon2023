import { Component, HostListener } from '@angular/core';

import { CommunicationService } from '../../shared/communication.service';
import { Manual } from './manual.model';

@Component({
  selector: 'app-manual',
  templateUrl: './manual.component.html',
  styleUrls: ['./manual.component.css']
})
export class ManualComponent {
  currentManual: Manual = new Manual(false, false, false, false);

  constructor(private communicationService: CommunicationService) { }

  onForward() {
    this.currentManual.up = !this.currentManual.up;
    this.currentManual.down = false;
    this.currentManual.right = false;
    this.currentManual.left = false;
    // if (this.currentManual.up && this.currentManual.down) {
    //   this.currentManual.down = !this.currentManual.down;
    // }
    this.communicationService.setManual(this.currentManual);
    console.log("onForward");
  }

  onBackward() {
    this.currentManual.down = !this.currentManual.down;
    this.currentManual.up = false;
    this.currentManual.right = false;
    this.currentManual.left = false;
    // if (this.currentManual.up && this.currentManual.down) {
    //   this.currentManual.up = !this.currentManual.up;
    // }
    this.communicationService.setManual(this.currentManual);
  }

  onRightTurn() {
    this.currentManual.right = !this.currentManual.right;
    this.currentManual.down = false;
    this.currentManual.up = false;
    this.currentManual.left = false;
    // if (this.currentManual.right && this.currentManual.left) {
    //   this.currentManual.left = !this.currentManual.left;
    // }
    this.communicationService.setManual(this.currentManual);
  }

  onLeftTurn() {
    this.currentManual.left = !this.currentManual.left;
    this.currentManual.down = false;
    this.currentManual.right = false;
    this.currentManual.up = false;
    // if (this.currentManual.right && this.currentManual.left) {
    //   this.currentManual.right = !this.currentManual.right;
    // }
    this.communicationService.setManual(this.currentManual);
  }

  @HostListener('window:keyup', ['$event'])
  keyEvent(event: KeyboardEvent) {
    console.log(event);

    if (event.keyCode === 40) {
      this.onBackward();
    }

    if (event.keyCode === 39) {
      this.onRightTurn();
    }

    if (event.keyCode === 38) {
      this.onForward();
    }

    if (event.keyCode === 37) {
      this.onLeftTurn();
    }
  }
}
