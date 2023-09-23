import { Component, OnInit } from '@angular/core';

import { CommunicationService } from '../shared/communication.service';

@Component({
  selector: 'app-status',
  templateUrl: './status.component.html',
  styleUrls: ['./status.component.css']
})
export class StatusComponent {

  statusFirebaseData: any;

  constructor(private communicationService: CommunicationService) { }

  ngOnInit() {
    const firebasePath = 'status';
    this.communicationService.getData(firebasePath).subscribe((data) => {
      this.statusFirebaseData = data;
    })
  }
}
